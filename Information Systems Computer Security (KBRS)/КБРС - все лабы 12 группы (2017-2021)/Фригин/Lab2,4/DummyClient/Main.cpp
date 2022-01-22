#include <iostream>
#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

#include <Shared/RSA.hpp>
#include <Shared/Idea.hpp>
#include <Shared/MessageType.hpp>
#include <Shared/Idea.hpp>

static int ReadSessionKey (boost::asio::ip::tcp::socket &socket, std::array <uint8_t, 1024> &buffer,
                           const RSA::PrivateKey &rsaPrivateKey, Idea::Key &currentSessionKey)
{
    BOOST_LOG_TRIVIAL (info) << "Waiting for session key...";
    boost::asio::read (socket, boost::asio::buffer (buffer, 1 + RSA::MESSAGE_SIZE),
                       boost::asio::transfer_all ());

    if (buffer[0] != (uint8_t) MessageType::STC_SESSION_KEY)
    {
        BOOST_LOG_TRIVIAL(error) << "Expected message with code " << (uint8_t) MessageType::STC_SESSION_KEY <<
                                 ", but received " << buffer[0] << ".";
        return 1;
    }

    boost::multiprecision::int256_t sessionKey;
    boost::multiprecision::import_bits (sessionKey, buffer.begin () + 1,
                                        buffer.begin () + 1 + RSA::MESSAGE_SIZE);
    BOOST_LOG_TRIVIAL (debug) << "Received encoded session key: " << sessionKey << ".";

    RSA::Decode (rsaPrivateKey, sessionKey);
    BOOST_LOG_TRIVIAL (debug) << "Decoded session key: " << sessionKey << ".";

    // Clean buffer, so we'll be able to check if decoded session key size is really 128 bits.
    buffer.fill (0);
    boost::multiprecision::export_bits (sessionKey, buffer.begin () + 1, 8);
    std::copy (buffer.begin () + 1, buffer.begin () + 1 + RSA::MESSAGE_SIZE / 2, currentSessionKey.begin ());

    for (int index = RSA::MESSAGE_SIZE / 2; index < RSA::MESSAGE_SIZE; ++index)
    {
        if (buffer[index + 1] > 0)
        {
            BOOST_LOG_TRIVIAL(error) << "Unable to downcast decoded session key to 128 bits!";
            return 1;
        }
    }

    return 0;
}

int main (int argc, char *argv[])
{
    try
    {
        if (argc != 3)
        {
            std::cout << "Usage:" << std::endl << "    <executable> <host> <port>" << std::endl;
            return 1;
        }

        boost::asio::io_context ioContext;
        boost::asio::ip::tcp::resolver resolver (ioContext);
        boost::asio::ip::tcp::resolver::results_type endpoints =
            resolver.resolve (boost::asio::ip::tcp::v4 (), argv[1], argv[2]);

        boost::asio::ip::tcp::socket socket (ioContext);
        boost::asio::connect (socket, endpoints);

        BOOST_LOG_TRIVIAL (info) << "Connected to server!";

        RSA::PublicKey rsaPublicKey;
        RSA::PrivateKey rsaPrivateKey;
        Idea::Key currentSessionKey;
        std::array <uint8_t, 1024> buffer;

        BOOST_LOG_TRIVIAL (info) << "Initializing and sending public RSA key...";
        {
            RSA::GenerateKeys (rsaPublicKey, rsaPrivateKey);
            BOOST_LOG_TRIVIAL (debug) << "Generated RSA public key: n = " << rsaPublicKey.n <<
                                      ", e = " << rsaPublicKey.e << ".";

            buffer[0] = (uint8_t) MessageType::CTS_RSA_KEY;

            boost::multiprecision::export_bits (rsaPublicKey.n, buffer.begin () + 1, 8);
            boost::multiprecision::export_bits (rsaPublicKey.e, buffer.begin () + 1 + RSA::PublicKey::N_SIZE, 8);
            boost::asio::write (socket,
                                boost::asio::buffer (buffer, 1 + RSA::PublicKey::N_SIZE + RSA::PublicKey::E_SIZE),
                                boost::asio::transfer_all ());
        }

        {
            int readSessionKeyResult = ReadSessionKey (socket, buffer, rsaPrivateKey, currentSessionKey);
            if (readSessionKeyResult != 0)
            {
                return readSessionKeyResult;
            }
        }

        std::string login = "testlogin";
        std::string password = "testpassword";

        BOOST_LOG_TRIVIAL (info) << "Sending auth info...";
        {
            Idea::Block initialBlock;
            Idea::GenerateInitialBlock (initialBlock);

            std::stringbuf messageBuffer;
            std::ostream outputStream (&messageBuffer);

            outputStream.put ((char) MessageType::CTS_AUTH_REQUEST);
            outputStream.write ((const char *) &initialBlock[0], initialBlock.size ());
            outputStream.put ((uint8_t) login.size ());
            outputStream.put ((uint8_t) password.size ());

            std::istringstream loginPasswordStream (login + password);
            Idea::EncodeCBC (initialBlock, currentSessionKey,
                             Idea::StreamProducer (loginPasswordStream), Idea::StreamConsumer (outputStream));

            std::string message = messageBuffer.str ();
            std::copy (message.begin (), message.end (), buffer.begin ());
            boost::asio::write (socket, boost::asio::buffer (buffer, message.size ()), boost::asio::transfer_all ());
        }

        BOOST_LOG_TRIVIAL (info) << "Waiting for auth response...";
        {
            boost::asio::read (socket, boost::asio::buffer (buffer, 1), boost::asio::transfer_all ());
            if (buffer[0] != (uint8_t) MessageType::STC_AUTH_SUCCESSFUL)
            {
                BOOST_LOG_TRIVIAL(error) << "Expected message with code " <<
                                         (uint8_t) MessageType::STC_AUTH_SUCCESSFUL <<
                                         ", but received " << buffer[0] << ".";
                return 1;
            }
        }

        uint32_t requestsCount = 3;
        std::string testFileName = "test.txt";
        BOOST_LOG_TRIVIAL (info) << "Requesting file " << requestsCount << " times...";

        for (uint32_t index = 0; index < requestsCount; ++index)
        {
            BOOST_LOG_TRIVIAL (info) << "Requesting file...";
            {
                Idea::Block initialBlock;
                Idea::GenerateInitialBlock (initialBlock);

                std::stringbuf messageBuffer;
                std::ostream outputStream (&messageBuffer);

                outputStream.put ((char) MessageType::CTS_FILE_REQUEST);
                outputStream.write ((const char *) &initialBlock[0], initialBlock.size ());
                outputStream.put ((uint8_t) testFileName.size ());

                std::istringstream fileNameStream (testFileName);
                Idea::EncodeCBC (initialBlock, currentSessionKey,
                                 Idea::StreamProducer (fileNameStream), Idea::StreamConsumer (outputStream));

                std::string message = messageBuffer.str ();
                std::copy (message.begin (), message.end (), buffer.begin ());
                boost::asio::write (socket,
                                    boost::asio::buffer (buffer, message.size ()),
                                    boost::asio::transfer_all ());
            }

            BOOST_LOG_TRIVIAL (info) << "Reading file...";
            {
                boost::asio::read (socket,
                                   boost::asio::buffer (buffer, 1 + Idea::BLOCK_SIZE + sizeof (uint32_t)),
                                   boost::asio::transfer_all ());

                Idea::Block initialBlock;
                std::copy (buffer.begin () + 1, buffer.begin () + 1 + Idea::BLOCK_SIZE, initialBlock.begin ());
                uint32_t fileSize = *(uint32_t *) &buffer[1 + initialBlock.size ()];

                if (buffer[0] != (uint8_t) MessageType::STC_FILE)
                {
                    BOOST_LOG_TRIVIAL(error) << "Expected message with code " <<
                                             (uint8_t) MessageType::STC_AUTH_SUCCESSFUL <<
                                             ", but received " << buffer[0] << ".";
                    return 1;
                }

                uint32_t blocksLeft = fileSize / Idea::BLOCK_SIZE;
                if (fileSize % Idea::BLOCK_SIZE > 0)
                {
                    ++blocksLeft;
                }

                const uint32_t blocksInChunk = buffer.size () / Idea::BLOCK_SIZE;
                while (blocksLeft > 0)
                {
                    uint32_t blocksToRead = std::min (blocksInChunk, blocksLeft);
                    boost::asio::read (socket,
                                       boost::asio::buffer (buffer, blocksToRead * Idea::BLOCK_SIZE),
                                       boost::asio::transfer_all ());

                    std::stringbuf decodedBuffer;
                    std::ostream decodedStream (&decodedBuffer);

                    initialBlock = Idea::DecodeCBC (
                        initialBlock, currentSessionKey,
                        Idea::ByteIteratorProducer (buffer.begin (), buffer.begin () + blocksToRead * Idea::BLOCK_SIZE),
                        Idea::StreamConsumer (decodedStream));

                    std::cout << decodedBuffer.str ();
                    if (blocksLeft > blocksInChunk)
                    {
                        blocksLeft -= blocksInChunk;
                    }
                    else
                    {
                        blocksLeft = 0;
                    }
                }
            }

            if (index != requestsCount - 1)
            {
                int readSessionKeyResult = ReadSessionKey (socket, buffer, rsaPrivateKey, currentSessionKey);
                if (readSessionKeyResult != 0)
                {
                    return readSessionKeyResult;
                }
            }
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what () << "\n";
    }

    return 0;
}
