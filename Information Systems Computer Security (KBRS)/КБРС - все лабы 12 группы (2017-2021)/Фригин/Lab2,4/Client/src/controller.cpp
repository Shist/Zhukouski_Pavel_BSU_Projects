#include "client/controller.h"
#include <Shared/MessageType.hpp>
#include <iostream>
#include <sstream>
#include <QDebug>

Idea::Key ReadSessionKey(boost::asio::ip::tcp::socket& socket, RSA::PrivateKey& key) {
    std::array <uint8_t, 1024> buffer;
    boost::asio::read(socket, boost::asio::buffer (buffer, RSA::MESSAGE_SIZE), boost::asio::transfer_all());

    boost::multiprecision::int256_t sessionKey;
    boost::multiprecision::import_bits (sessionKey, buffer.begin (), buffer.begin () + RSA::MESSAGE_SIZE);

    RSA::Decode(key, sessionKey);
    Idea::Key result;


    // Clean buffer, so we'll be able to check if decoded session key size is really 128 bits.
    buffer.fill(0);
    boost::multiprecision::export_bits(sessionKey, buffer.begin (), 8);
    std::copy(buffer.begin (), buffer.begin () + RSA::MESSAGE_SIZE / 2, result.begin());

    return result;
}

Controller::Controller(QObject *parent) : QObject(parent)
{
    _ioContext = std::make_unique<boost::asio::io_context>();
}

ServerConnectionResult* Controller::connectToServer(QString address, QString port)
{
    // connect to server
    try {
        boost::asio::ip::tcp::resolver resolver (*_ioContext);
        boost::asio::ip::tcp::resolver::results_type endpoints =
        resolver.resolve(boost::asio::ip::tcp::v4 (), address.toStdString(), port.toStdString());
        _serverSocket = std::make_unique<boost::asio::ip::tcp::socket>(*_ioContext);
        boost::asio::connect (*_serverSocket, endpoints);
    }  catch (std::exception& e) {
        QString message = QString("Could not connect to server: ") + e.what() + '.';
        return new ServerConnectionResult(parent(), address, port, false, message);
    }

    // send RSA public key
    try {
        RSA::GenerateKeys(_crypto.rsaPublicKey, _crypto.rsaPrivateKey);

        std::array <uint8_t, 1024> buffer;
        buffer[0] = (uint8_t) MessageType::CTS_RSA_KEY;
        boost::multiprecision::export_bits (_crypto.rsaPublicKey.n, buffer.begin () + 1, 8);
        boost::multiprecision::export_bits (_crypto.rsaPublicKey.e, buffer.begin () + 1 + RSA::PublicKey::N_SIZE, 8);
        boost::asio::write (*_serverSocket, boost::asio::buffer (buffer, 1 + RSA::PublicKey::N_SIZE + RSA::PublicKey::E_SIZE),
                            boost::asio::transfer_all());
    }  catch (std::exception& e) {
        QString message = QString("Could not send RSA public key: ") + e.what() + '.';
        return new ServerConnectionResult(parent(), address, port, false, message);
    }

    // receive session key
    try {
        std::array <uint8_t, 1> buffer;
        boost::asio::read(*_serverSocket, boost::asio::buffer(buffer, 1), boost::asio::transfer_all());

        if (buffer[0] != (uint8_t) MessageType::STC_SESSION_KEY)
            throw std::runtime_error("Received message has unexpected type.");

       _crypto.currentSessionKey = ReadSessionKey(*_serverSocket, _crypto.rsaPrivateKey);
    }  catch (std::exception& e) {
        QString message = QString("Could not receive session key: ") + e.what() + '.';
        return new ServerConnectionResult(parent(), address, port, false, message);
    }

    return new ServerConnectionResult(parent(), address, port, true, "Ok");
}

AuthenticationResult* Controller::authenticate(QString login, QString password)
{
    std::array <uint8_t, 1024> buffer;
    // send auth info
    try {
        Idea::Block initialBlock;
        Idea::GenerateInitialBlock (initialBlock);

        std::stringbuf messageBuffer;
        std::ostream outputStream (&messageBuffer);

        outputStream.put ((char) MessageType::CTS_AUTH_REQUEST);
        outputStream.write ((const char *) &initialBlock[0], initialBlock.size ());
        outputStream.put ((uint8_t) login.size ());
        outputStream.put ((uint8_t) password.size ());

        std::istringstream loginPasswordStream (login.toStdString() + password.toStdString());
        Idea::EncodeCBC (initialBlock, _crypto.currentSessionKey,
                    Idea::StreamProducer (loginPasswordStream), Idea::StreamConsumer (outputStream));

        std::string message = messageBuffer.str ();
        std::copy (message.begin (), message.end (), buffer.begin ());
        boost::asio::write (*_serverSocket, boost::asio::buffer (buffer, message.size ()), boost::asio::transfer_all ());
    } catch(std::exception& e) {
        return new AuthenticationResult(parent(), login, false, "Could not send auth info");
    }

    // receive auth response
    try {
        boost::asio::read (*_serverSocket, boost::asio::buffer (buffer, 1), boost::asio::transfer_all ());

        if (buffer[0] == (uint8_t) MessageType::STC_AUTH_SUCCESSFUL)
            return new AuthenticationResult(parent(), login, true, "Ok");

        std::stringstream message;
        message << "Expected message with code " <<
                   (uint8_t) MessageType::STC_AUTH_SUCCESSFUL <<
                   ", but received " << buffer[0] << ".";
        throw std::runtime_error(message.str());
    }  catch (std::exception& e) {
        return new AuthenticationResult(parent(), login, false, "Could not receive auth response");
    }
}

FileInfo* Controller::loadFile(QString filename)
{
    std::array <uint8_t, 1024> buffer;
    // request file
    try {
        Idea::Block initialBlock;
        Idea::GenerateInitialBlock (initialBlock);

        std::stringbuf messageBuffer;
        std::ostream outputStream (&messageBuffer);

        outputStream.put ((char) MessageType::CTS_FILE_REQUEST);
        outputStream.write ((const char *) &initialBlock[0], initialBlock.size ());
        outputStream.put ((uint8_t) filename.toStdString().size ());

        std::istringstream fileNameStream (filename.toStdString());
        Idea::EncodeCBC (initialBlock, _crypto.currentSessionKey,
                        Idea::StreamProducer (fileNameStream), Idea::StreamConsumer (outputStream));

        std::string message = messageBuffer.str ();
        std::copy (message.begin (), message.end (), buffer.begin ());
        boost::asio::write (*_serverSocket, boost::asio::buffer (buffer, message.size ()), boost::asio::transfer_all ());
    }  catch (std::exception& e) {
        return new FileInfo(parent(), "Could not send file request");
    }

    // receive file
    try {

        for (;;) {
            boost::asio::read (*_serverSocket, boost::asio::buffer(buffer, 1), boost::asio::transfer_all ());

            if (buffer[0] == (uint8_t) MessageType::STC_FILE)
                break;

            if (buffer[0] == (uint8_t) MessageType::STC_UNABLE_TO_SEND_FILE)
                throw std::runtime_error("Unable to send file. Maybe file not found.");

            if (buffer[0] == (uint8_t)MessageType::STC_SESSION_KEY) {
                _crypto.currentSessionKey = ReadSessionKey(*_serverSocket, _crypto.rsaPrivateKey);
                continue;
            }

            std::stringstream message;
            message << "Unexpected protocol message type. Expected: " <<
                 (unsigned int) MessageType::STC_FILE << ", but received " << (unsigned int) buffer[0];
            throw std::runtime_error(message.str());
        }


        // read filesize
        boost::asio::read (*_serverSocket,
                            boost::asio::buffer(buffer.begin() + 1, Idea::BLOCK_SIZE + 4),
                            boost::asio::transfer_all ());

        Idea::Block initialBlock;
        std::copy (buffer.begin() + 1, buffer.begin() + 1 + Idea::BLOCK_SIZE, initialBlock.begin());
        std::uint32_t fileSize = *(std::uint32_t *)&buffer[1 + initialBlock.size()];

        qDebug() << "Filesize: " << fileSize << " bytes";

        std::uint32_t blocksLeft = fileSize / Idea::BLOCK_SIZE;
        if (fileSize % Idea::BLOCK_SIZE > 0)
            ++blocksLeft;

        const std::uint32_t blocksInChunk = buffer.size () / Idea::BLOCK_SIZE;

        std::stringstream text;
        while (blocksLeft > 0)
        {
            std::uint32_t blocksToRead = std::min (blocksInChunk, blocksLeft);
            boost::asio::read (*_serverSocket,
               boost::asio::buffer (buffer, blocksToRead * Idea::BLOCK_SIZE),
               boost::asio::transfer_all ());

            std::stringbuf decodedBuffer;
            std::ostream decodedStream(&decodedBuffer);

            initialBlock = Idea::DecodeCBC(initialBlock, _crypto.currentSessionKey,
                Idea::ByteIteratorProducer (buffer.begin (), buffer.begin () + blocksToRead * Idea::BLOCK_SIZE),
                Idea::StreamConsumer (decodedStream));
            //std::cout << decodedBuffer.str();
            text << decodedBuffer.str();
            if (blocksLeft > blocksInChunk)
                blocksLeft -= blocksInChunk;
            else
                blocksLeft = 0;
        }
        std::string strText = text.str();
        for (char& c : strText)
            if (c > 127)
                c = '?';
        std::cout << strText << std::endl;
        return new FileInfo(parent(), filename, QString::fromStdString(strText));
    } catch (std::exception& e) {
        return new FileInfo(parent(), e.what());
    }
}

void Controller::reset()
{
    try {
        //_serverSocket->shutdown();
        _serverSocket->close();
        _serverSocket.reset();
    }
    catch(...)
    {}
}
