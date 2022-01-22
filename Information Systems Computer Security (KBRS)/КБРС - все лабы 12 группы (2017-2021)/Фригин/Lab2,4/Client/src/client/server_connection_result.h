#ifndef SERVER_CONNECTION_RESULT_H
#define SERVER_CONNECTION_RESULT_H

#include <QObject>

class ServerConnectionResult : public QObject {
    Q_OBJECT

public:
    ServerConnectionResult() = default;
    ServerConnectionResult(QObject* parent, QString address, QString port, bool isConnected, QString reason);
    ServerConnectionResult& operator=(ServerConnectionResult&& other) noexcept;

    Q_INVOKABLE bool isConnected();
    Q_INVOKABLE QString reason();
    Q_INVOKABLE QString address();
    Q_INVOKABLE QString port();

private:
    bool _isConnected;
    QString _reason;
    QString _address;
    QString _port;
};

#endif // SERVER_CONNECTION_RESULT_H
