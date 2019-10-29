/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Contacts
*/

#include <iostream>

#include "Contacts.hpp"
#include "Network.hpp"

Contacts::Contacts(QObject *parent) :
    QObject(parent)
{
    auto client {Network::getInstance()->getClient()};
    client->addCallback(Request::Type::FRIEND_INFO, [this](Request &req) {
        getFriends();
    });
    client->addCallback(Request::Type::REMOVE_FRIEND, [this](Request &req) {
        getFriends();
    });
}

QStringList Contacts::friendList() const
{
    return _friendsList;
}

void Contacts::getFriends()
{
    auto client {Network::getInstance()->getClient()};
    auto friends = client->getFriends();

    _friendsList.clear();
    QString l;
    for (auto const &f : friends) {
        l = QString::fromUtf8(f.name) + "." + QString::fromUtf8(std::to_string(f.id).c_str()) + "." + QString::fromUtf8(f.connected ? "Online" : "Offline");
        _friendsList.append(l);
    }
    emit friendListChanged();
}

QString Contacts::addFriend(QString name)
{
    if (name == "") {
        return "You have to type a username";
    }
    auto client {Network::getInstance()->getClient()};
    auto match = client->autocompleteFriends(name.toStdString());
    if (match.size() == 0) {
        return "Unknow username";
    }
    auto needle = std::string(match[0].name);
    for (int i = 0; i < _friendsList.size(); i++) {
        if (_friendsList[i].toStdString().find(needle) != std::string::npos)
            return QString::fromUtf8(std::string(std::string("You already have ") + 
                std::string(match[0].name) + std::string(" as friend")).c_str());
    }   
    client->addFriend(match[0].id);
    return "OK";
}

void Contacts::removeFriend(QString name)
{
    auto client {Network::getInstance()->getClient()};
    auto match = client->autocompleteFriends(name.toStdString());

    client->removeFriend(match[0].id);
}

void Contacts::debug(QString s) const
{
    std::cout << "[DEBUG] : " << s.toStdString() << std::endl;
}