#ifndef AUTHENTICATION_RESULT_H
#define AUTHENTICATION_RESULT_H

#include <QObject>

/**
 * @brief Authentication result
 */
class AuthenticationResult : public QObject {
    Q_OBJECT
public:
    AuthenticationResult() = default;
    AuthenticationResult(QObject* parent, QString login, bool is_authenticated, QString reason);
    AuthenticationResult& operator=(AuthenticationResult&& other) noexcept;

    Q_INVOKABLE QString login();
    Q_INVOKABLE bool isAuthenticated();
    Q_INVOKABLE QString reason();

private:
    bool _isAuthenticated;
    QString _login;
    QString _reason;
};

#endif // AUTHENTICATION_RESULT_H
