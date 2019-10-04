/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Call
*/

#include <QQuickItem>
#include <QQuickView>
#include <QDebug>
#include <QSignalSpy>
#include <QTest>

#include "Call.hpp"
#include "Network.hpp"

Call::Call(QObject *parent) :
    _calling(false), _targetName(""), _targetId(-1)
{
    auto client {Network::getInstance()->getClient()};

    client->setCallCallback([this](int callerId) -> bool {
        emit this->callingYou(callerId);
        auto engine = Engine::getInstance(nullptr)->getQmlEngine();
        QObject* home = engine->rootObjects().first()->findChild<QObject*>("ContactObject");
        QObject::connect(home, SIGNAL(clickedAccept()), this, SLOT(onClickedAccept()));
        QObject::connect(home, SIGNAL(clickedDeny()), this, SLOT(onClickedDeny()));
    
        QSignalSpy spyAccept(home, SIGNAL(clickedAccept()));
        QSignalSpy spyDeny(home, SIGNAL(clickedDeny()));
    
        for (int waitDelay = 500000; waitDelay > 0 && spyAccept.count() == 0
            && spyDeny.count() == 0; waitDelay -= 100) {
            QTest::qWait(100);
        }
        return _callAccepted;
    });
}

void Call::onClickedAccept()
{
    _callAccepted = true;
    _calling = true;
}

void Call::onClickedDeny()
{
    _callAccepted = false;
}

Call &Call::operator=(Call const &other)
{
    if (this != &other) {
        _calling = other._calling;
        _targetName = other._targetName;
        _targetId = other._targetId;
        // _engine = other._engine;
    }
    return *this;
}

Call::Call(Call const &other)
{
    _calling = other._calling;
    _targetName = other._targetName;
    _targetId = other._targetId;
    // _engine = other._engine;
}

Q_INVOKABLE bool Call::requestCall(QString name)
{
    auto client {Network::getInstance()->getClient()};
    _targetName = name.toUtf8().constData();

    auto friends {client->autocompleteFriends(_targetName)};
    _targetId = friends[0].id;

    client->call(_targetId);
    _calling = true;
    return true;
}

Q_INVOKABLE void Call::stopCall()
{
    auto client {Network::getInstance()->getClient()};

    client->stopCall();
    this->reset();
}

void Call::reset()
{
    _targetName = "";
    _targetId = -1;
    _calling = false;
}