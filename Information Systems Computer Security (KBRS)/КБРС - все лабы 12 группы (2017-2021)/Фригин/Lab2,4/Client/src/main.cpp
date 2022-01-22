#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "client/controller.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    Controller controller(&engine);
    engine.rootContext()->setContextProperty("controller", &controller);
    qmlRegisterInterface<ServerConnectionResult>("ServerConnectionResult", 1);
    qmlRegisterInterface<AuthenticationResult>("AuthenticationResult", 1);
    qmlRegisterInterface<FileInfo>("FileInfo", 1);

    engine.load(url);
    return app.exec();
}
