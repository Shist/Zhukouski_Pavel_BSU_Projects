#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <boost/asio.hpp>

#include "server_connection_result.h"
#include "authentication_result.h"
#include "file_info.h"

#include <Shared/RSA.hpp>
#include <Shared/Idea.hpp>

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(QObject *parent = nullptr);

public slots:
    Q_INVOKABLE ServerConnectionResult* connectToServer(QString address, QString port);
    Q_INVOKABLE AuthenticationResult* authenticate(QString login, QString password);
    Q_INVOKABLE FileInfo* loadFile(QString filename);
    Q_INVOKABLE void reset();

private:
    std::unique_ptr<boost::asio::io_context> _ioContext;
    std::unique_ptr<boost::asio::ip::tcp::socket> _serverSocket;
    struct {
        RSA::PublicKey rsaPublicKey;
        RSA::PrivateKey rsaPrivateKey;
        Idea::Key currentSessionKey;
    } _crypto;

};

#endif // CONTROLLER_H
