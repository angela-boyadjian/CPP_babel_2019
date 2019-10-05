/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** main
*/

#include <QQuickStyle>
#include <QSettings>

#include "Engine.hpp"

#include "Worker.hpp"
#include "Contacts.hpp"
#include "Login.hpp"
#include "Network.hpp"
#include "Settings.hpp"
#include "Call.hpp"
#include "Messager.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    auto app = new QGuiApplication(argc, argv);

    auto instance = Engine::getInstance(app);

    QQuickStyle::setStyle("Material");
    QCoreApplication::setOrganizationName("Epitech");
    QCoreApplication::setApplicationName("Babel");

    qmlRegisterType<Login>("babel.qt.login", 1, 0, "Login");
    qmlRegisterType<Contacts>("babel.qt.contacts", 1, 0, "Contacts");
    qmlRegisterType<Worker>("babel.qt.worker", 1, 0, "Worker");
    qmlRegisterType<Settings>("babel.qt.settings", 1, 0, "Settings");
    qmlRegisterType<Call>("babel.qt.call", 1, 0, "Call");
    qmlRegisterType<Messager>("babel.qt.messager", 1, 0, "Messager");

    QSettings s("Babel", "Epitech");

    auto engine = instance->getQmlEngine();
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(engine, &QQmlApplicationEngine::objectCreated,
                    app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine->load(url);
    auto ret {app->exec()};
    delete engine;
    delete app;
    return ret;
}