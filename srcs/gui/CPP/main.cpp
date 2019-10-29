/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** main
*/

#include "Engine.hpp"

#include "Worker.hpp"
#include "Contacts.hpp"
#include "Login.hpp"
#include "Network.hpp"
#include "Settings.hpp"
#include "Call.hpp"
#include <QQuickStyle>
#include <QSettings>
#include "Messager.hpp"
#include "../../common/Args.hpp"
#include "logger.hpp"
#include "Profil.hpp"

int main(int argc, char *argv[])
{
    try {
        auto args = Args(argc, argv);
        Network::setPorts(args.tcpport, args.udpport);

        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        qInstallMessageHandler(qtOutputHandling);
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
        qmlRegisterType<Profil>("babel.qt.profil", 1, 0, "Profil");
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
        int ret = app->exec();
        delete engine;
        delete app;
        return ret;
    } catch (const ArgsHelp &e) {
        return 0;
    } catch (const ArgsInvalidArgument &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (...) {
        std::cerr << "Unknown error" << std::endl;
        return 84;
    }
    return 0;
}