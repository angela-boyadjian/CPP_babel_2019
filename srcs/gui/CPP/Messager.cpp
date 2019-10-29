/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Messager
*/

#include <QDebug>

#include <iostream>

#include "Messager.hpp"
#include "Network.hpp"


Messager::Messager(QObject *parent) :
    _msg(" ")
{
    auto client {Network::getInstance()->getClient()};

    client->addCallback(Request::Type::MESSAGE, [this](Request &req) {
        auto data {req.data.message};
        _msg = QString::fromUtf8(data.message);
        emit this->receivedMessage(data.targetId, data.senderId, _msg);
    });
}

void Messager::sendMessage(QString const &msg, int targetId)
{
    qDebug() << "Sending message : " << msg << " to " << targetId;
    auto client {Network::getInstance()->getClient()};
    std::string tmp = msg.toStdString();
    char const *toSend = tmp.c_str();
    _msg = msg; 
    client->sendMessage(toSend, targetId);
}

QString Messager::getMessage()
{
    return _msg;
}