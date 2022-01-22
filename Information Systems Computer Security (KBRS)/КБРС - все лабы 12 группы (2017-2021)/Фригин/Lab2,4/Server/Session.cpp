#include "Session.hpp"
#include <boost/random.hpp>
#include <boost/log/trivial.hpp>

#include <ctime>
#include <fstream>

#include <Shared/MessageType.hpp>
#include "AuthService.hpp"
#include "FileService.hpp"
#include "TimerService.hpp"

namespace States
{
const char *INITIAL = "Initial";

const char *SESSION_KEY_GENERATION = "SessionKeyGeneration";

const char *WAITING_FOR_AUTH = "WaitingForAuth";

const char *VALIDATING_AUTH = "ValidatingAuth";

const char *WAITING_FOR_QUERIES = "WaitingForQueries";

const char *SENDING_FILE = "SendingFile";
}

static const clock_t SESSION_KEY_UPDATE_PERIOD = 20 * CLOCKS_PER_SEC;

Session::Session (boost::asio::io_context &ioContext)
    : socket_ (ioContext)
{
}

Session::~Session ()
{
    BOOST_LOG_TRIVIAL (info) << "Session [" << this << "]: Ended!";
}

boost::asio::ip::tcp::socket &Session::GetSocket ()
{
    return socket_;
}

void Session::Start ()
{
    BOOST_LOG_TRIVIAL (info) << "Session [" << this << "]: Started!";

    stateMachine_ = std::make_unique <StateMachine> (
        std::unordered_map <std::string, StateMachine::State> {
            {
                States::INITIAL,
                {
                    [this] (StateMachine &owner) -> std::optional <char>
                    {
                        BOOST_LOG_TRIVIAL (info) << "Session [" << this << "]: Entered state " <<
                                                 States::INITIAL << "!";
                        AsyncWaitForInput (1 + RSA::PublicKey::N_SIZE + RSA::PublicKey::E_SIZE);
                        return {};
                    },
                    {
                        {
                            (char) MessageType::CTS_RSA_KEY,
                            [this] () -> std::string
                            {
                                ReadRSAKey ();
                                return States::SESSION_KEY_GENERATION;
                            }
                        }
                    }
                }
            },

            {
                States::SESSION_KEY_GENERATION,
                {
                    [this] (StateMachine &owner) -> std::optional <char>
                    {
                        BOOST_LOG_TRIVIAL (info) << "Session [" << this << "]: Entered state " <<
                                                 States::SESSION_KEY_GENERATION << "!";

                        GenerateSessionKey ();
                        return (char) MessageType::STC_SESSION_KEY;
                    },
                    {
                        {
                            (char) MessageType::STC_SESSION_KEY,
                            [this] () -> std::string
                            {
                                WriteSessionKey ();
                                return States::WAITING_FOR_AUTH;
                            }
                        }
                    }
                }
            },

            {
                States::WAITING_FOR_AUTH,
                {
                    [this] (StateMachine &owner) -> std::optional <char>
                    {
                        BOOST_LOG_TRIVIAL (info) << "Session [" << this << "]: Entered state " <<
                                                 States::WAITING_FOR_AUTH << "!";
                        AsyncWaitForInput (1 + Idea::BLOCK_SIZE + sizeof (uint8_t) * 2);
                        return {};
                    },
                    {
                        {
                            (char) MessageType::CTS_AUTH_REQUEST,
                            [this] () -> std::string
                            {
                                return States::VALIDATING_AUTH;
                            }
                        }
                    }
                }
            },

            {
                States::VALIDATING_AUTH,
                {
                    [this] (StateMachine &owner) -> std::optional <char>
                    {
                        BOOST_LOG_TRIVIAL (info) << "Session [" << this << "]: Entered state " <<
                                                 States::VALIDATING_AUTH << "!";
                        return (char) (ReadAndValidateAuth () ?
                                       MessageType::STC_AUTH_SUCCESSFUL : MessageType::STC_AUTH_FAILED);
                    },
                    {
                        {
                            (char) MessageType::STC_AUTH_SUCCESSFUL,
                            [this] () -> std::string
                            {
                                buffer_[0] = (char) MessageType::STC_AUTH_SUCCESSFUL;
                                boost::system::error_code error;

                                boost::asio::write (socket_, boost::asio::buffer (buffer_, 1),
                                                    boost::asio::transfer_all (), error);

                                AbortOnFatalError (error);
                                StartSessionKeyUpdateTimer ();
                                return States::WAITING_FOR_QUERIES;
                            }
                        },

                        {
                            (char) MessageType::STC_AUTH_FAILED,
                            [this] () -> std::string
                            {
                                buffer_[0] = (char) MessageType::STC_AUTH_FAILED;
                                boost::system::error_code error;

                                boost::asio::write (socket_, boost::asio::buffer (buffer_, 1),
                                                    boost::asio::transfer_all (), error);

                                AbortOnFatalError (error);
                                return States::WAITING_FOR_AUTH;
                            }
                        }
                    }
                }
            },

            {
                States::WAITING_FOR_QUERIES,
                {
                    [this] (StateMachine &owner) -> std::optional <char>
                    {
                        BOOST_LOG_TRIVIAL (info) << "Session [" << this << "]: Entered state " <<
                                                 States::WAITING_FOR_QUERIES << "!";
                        AsyncWaitForInput (1 + Idea::BLOCK_SIZE + sizeof (uint8_t));
                        return {};
                    },
                    {
                        {
                            (char) MessageType::STC_SESSION_KEY,
                            [this] () -> std::string
                            {
                                GenerateSessionKey ();
                                WriteSessionKey ();
                                return States::WAITING_FOR_QUERIES;
                            }
                        },

                        {
                            (char) MessageType::CTS_FILE_REQUEST,
                            [this] () -> std::string
                            {
                                return States::SENDING_FILE;
                            }
                        }
                    }
                }
            },

            {
                States::SENDING_FILE,
                {
                    [this] (StateMachine &owner) -> std::optional <char>
                    {
                        BOOST_LOG_TRIVIAL (info) << "Session [" << this << "]: Entered state " <<
                                                 States::SENDING_FILE << "!";
                        return (char) (TrySendFile () ? MessageType::STC_FILE : MessageType::STC_UNABLE_TO_SEND_FILE);
                    },
                    {
                        {
                            (char) MessageType::STC_FILE,
                            [this] () -> std::string
                            {
                                return States::WAITING_FOR_QUERIES;
                            }
                        },

                        {
                            (char) MessageType::STC_UNABLE_TO_SEND_FILE,
                            [this] () -> std::string
                            {
                                buffer_[0] = (char) MessageType::STC_UNABLE_TO_SEND_FILE;
                                boost::system::error_code error;

                                boost::asio::write (socket_, boost::asio::buffer (buffer_, 1),
                                                    boost::asio::transfer_all (), error);

                                AbortOnFatalError (error);
                                return States::WAITING_FOR_QUERIES;
                            }
                        }
                    }
                }
            }
        },
        States::INITIAL
    );
}

void Session::Abort ()
{
    TimerService::RemoveAllTimers (this);
    delete this;
}

void Session::AbortOnFatalError (const boost::system::error_code &error)
{
    if (error)
    {
        BOOST_LOG_TRIVIAL (info) << "Session [" << this << "]: Caught error " << error << ", aborting...";
        Abort ();
        throw std::runtime_error ("Session aborted!");
    }
}

void Session::AsyncWaitForInput (uint32_t expectedCount)
{
    if (asyncWaitByteLimit_ == 0)
    {
        asyncWaitByteLimit_ = expectedCount;
        boost::asio::async_read (socket_, boost::asio::buffer (buffer_),
                                 boost::asio::transfer_exactly (expectedCount),
                                 [this] (const boost::system::error_code &error,
                                         uint32_t bytesTransferred) -> void
                                 {
                                     AbortOnFatalError (error);
                                     asyncWaitByteLimit_ = 0;

                                     try
                                     {
                                         stateMachine_->Consume (buffer_[0]);
                                     }
                                     catch (StateMachine::UnsupportedCodeException &exception)
                                     {
                                         // TODO: Better exception logging.
                                         BOOST_LOG_TRIVIAL (info) << "Session [" << this << "]: Caught exception " <<
                                                                  exception.what () << ", aborting...";
                                         Abort ();
                                     }
                                     catch (StateMachine::StateNotExistsException &exception)
                                     {
                                         // TODO: Better exception logging.
                                         BOOST_LOG_TRIVIAL (info) << "Session [" << this << "]: Caught exception " <<
                                                                  exception.what () << ", aborting...";
                                         Abort ();
                                     }
                                 });
    }
    else if (asyncWaitByteLimit_ != expectedCount)
    {
        BOOST_LOG_TRIVIAL (info) << "Session [" << this << "]: Already waited for " << asyncWaitByteLimit_ <<
                                 " bytes, but received async wait request for " << expectedCount << " bytes!";
        Abort ();
        throw std::runtime_error ("Session aborted!");
    }
}

void Session::GenerateSessionKey ()
{
    boost::random::mt11213b base_gen (clock ());
    boost::random::independent_bits_engine <boost::random::mt11213b,
                                            Idea::KEY_SIZE * 8, boost::multiprecision::uint128_t> gen (base_gen);

    boost::multiprecision::uint128_t sessionKey = gen ();
    boost::multiprecision::export_bits (sessionKey, currentSessionKey_.begin (), 8);

    BOOST_LOG_TRIVIAL(debug) << "Session [" << this << "]: Generated session key " << sessionKey << ".";
}

void Session::ReadRSAKey ()
{
    auto nStart = buffer_.begin () + 1;
    auto nEnd = nStart + RSA::PublicKey::N_SIZE;
    auto eStart = nEnd;
    auto eEnd = eStart + RSA::PublicKey::E_SIZE;

    boost::multiprecision::import_bits (rsaPublicKey_.n, nStart, nEnd);
    boost::multiprecision::import_bits (rsaPublicKey_.e, eStart, eEnd);

    BOOST_LOG_TRIVIAL(debug) << "Session [" << this << "]: Received RSA public key: n = " << rsaPublicKey_.n <<
                             ", e = " << rsaPublicKey_.e << ".";
}

void Session::WriteSessionKey ()
{
    buffer_[0] = (uint8_t) MessageType::STC_SESSION_KEY;
    boost::multiprecision::int256_t sessionKey;
    boost::multiprecision::import_bits (sessionKey, currentSessionKey_.begin (), currentSessionKey_.end ());

    RSA::Encode (rsaPublicKey_, sessionKey);
    boost::multiprecision::export_bits (sessionKey, buffer_.begin () + 1, 8);

    boost::system::error_code error;
    boost::asio::write (socket_, boost::asio::buffer (buffer_, 1 + RSA::MESSAGE_SIZE),
                        boost::asio::transfer_all (), error);

    AbortOnFatalError (error);
    BOOST_LOG_TRIVIAL(debug) << "Session [" << this << "]: Encoded session key sent: " << sessionKey << "!";
}

bool Session::ReadAndValidateAuth ()
{
    Idea::Block initialBlock;
    std::copy (buffer_.begin () + 1, buffer_.begin () + 1 + initialBlock.size (), initialBlock.begin ());
    uint8_t loginSize = buffer_[1 + initialBlock.size ()];
    uint8_t passwordSize = buffer_[1 + initialBlock.size () + sizeof (uint8_t)];

    uint16_t stringSize = loginSize + passwordSize;
    uint16_t blockCount = stringSize / 8;

    if (stringSize % 8 > 0)
    {
        ++blockCount;
    }

    boost::system::error_code error;
    boost::asio::read (socket_, boost::asio::buffer (buffer_, blockCount * Idea::BLOCK_SIZE),
                       boost::asio::transfer_all (), error);

    AbortOnFatalError (error);
    std::stringbuf loginPasswordBuffer;
    std::ostream loginPasswordOutputStream (&loginPasswordBuffer);

    Idea::DecodeCBC (initialBlock, currentSessionKey_,
                     Idea::ByteIteratorProducer (buffer_.begin (), buffer_.begin () + Idea::BLOCK_SIZE * blockCount),
                     Idea::StreamConsumer (loginPasswordOutputStream));

    std::string login = loginPasswordBuffer.str ().substr (0, loginSize);
    std::string password = loginPasswordBuffer.str ().substr (loginSize, passwordSize);

    BOOST_LOG_TRIVIAL(debug) << "Session [" << this << "]: Received auth request with login \"" << login <<
                             "\" and password \"" + password + "\".";
    return AuthService::Check (login, password);
}

bool Session::TrySendFile ()
{
    Idea::Block initialBlock;
    std::copy (buffer_.begin () + 1, buffer_.begin () + 1 + initialBlock.size (), initialBlock.begin ());

    uint8_t fileNameSize = buffer_[1 + initialBlock.size ()];
    uint32_t blockCount = fileNameSize / 8;

    if (fileNameSize % 8 > 0)
    {
        ++blockCount;
    }

    boost::system::error_code error;
    boost::asio::read (socket_, boost::asio::buffer (buffer_, blockCount * Idea::BLOCK_SIZE),
                       boost::asio::transfer_all (), error);

    AbortOnFatalError (error);
    std::stringbuf fileNameBuffer;
    std::ostream fileNameStream (&fileNameBuffer);

    Idea::DecodeCBC (initialBlock, currentSessionKey_,
                     Idea::ByteIteratorProducer (buffer_.begin (), buffer_.begin () + Idea::BLOCK_SIZE * blockCount),
                     Idea::StreamConsumer (fileNameStream));

    std::string fileName = fileNameBuffer.str ().substr (0, fileNameSize);
    BOOST_LOG_TRIVIAL(debug) << "Session [" << this << "]: Received request for file \"" << fileName << "\".";

    std::ifstream inputFile = FileService::Resolve (fileName);
    if (!inputFile)
    {
        BOOST_LOG_TRIVIAL(debug) << "Session [" << this << "]: Unable to process request for file \"" <<
                                 fileName << "\"!";
        return false;
    }

    BOOST_LOG_TRIVIAL(debug) << "Session [" << this << "]: Sending file \"" << fileName << "\"...";
    inputFile.seekg (0, inputFile.end);
    uint32_t fileLength = inputFile.tellg ();
    inputFile.seekg (0, inputFile.beg);

    Idea::GenerateInitialBlock (initialBlock);
    buffer_[0] = (char) MessageType::STC_FILE;
    std::copy (initialBlock.begin (), initialBlock.end (), buffer_.begin () + 1);
    *(uint32_t *) &buffer_[1 + initialBlock.size ()] = fileLength;

    boost::asio::write (socket_, boost::asio::buffer (buffer_, 1 + Idea::BLOCK_SIZE + sizeof (uint32_t)),
                        boost::asio::transfer_all (), error);

    AbortOnFatalError (error);
    while (inputFile)
    {
        inputFile.read ((char *) &buffer_[0], buffer_.size ());
        uint32_t read = inputFile.gcount ();

        blockCount = read / 8;
        if (read % 8 > 0)
        {
            ++blockCount;
        }

        std::stringbuf encodedBuffer;
        std::ostream encodedStream (&encodedBuffer);

        initialBlock = Idea::EncodeCBC (
            initialBlock, currentSessionKey_,
            Idea::ByteIteratorProducer (buffer_.begin (), buffer_.begin () + Idea::BLOCK_SIZE * blockCount),
            Idea::StreamConsumer (encodedStream));

        std::string encoded = encodedBuffer.str ();
        std::copy (encoded.begin (), encoded.end (), buffer_.begin ());

        boost::asio::write (socket_, boost::asio::buffer (buffer_, Idea::BLOCK_SIZE * blockCount),
                            boost::asio::transfer_all (), error);
        AbortOnFatalError (error);
    }

    BOOST_LOG_TRIVIAL(debug) << "Session [" << this << "]: File \"" << fileName << "\" sent!";
    return true;
}

void Session::StartSessionKeyUpdateTimer ()
{
    TimerService::AddTimer ({this, clock () + SESSION_KEY_UPDATE_PERIOD,
                             [this] () -> bool
                             {
                                 if (stateMachine_->GetCurrentStateName () == States::WAITING_FOR_QUERIES)
                                 {
                                     stateMachine_->Consume ((char) MessageType::STC_SESSION_KEY);
                                     StartSessionKeyUpdateTimer ();
                                     return true;
                                 }
                                 else
                                 {
                                     return false;
                                 }
                             }});
}
