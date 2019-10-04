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
        l = QString::fromUtf8(f.name) + "." + QString::fromUtf8(std::to_string(f.id).c_str());
        _friendsList.append(l);
    }
    emit friendListChanged();
}

bool Contacts::addFriend(QString name) 
{
    auto client {Network::getInstance()->getClient()};
    auto match = client->autocompleteFriends(name.toStdString());

    if (match.size() == 0) {
        std::cout << "Unknow name" << std::endl; // TODO Err pop up
        return false;
    } else {
        client->addFriend(match[0].id);
        return true;
    }
}

void Contacts::removeFriend(QString name)
{
    auto client {Network::getInstance()->getClient()};
    auto match = client->autocompleteFriends(name.toStdString());

    client->removeFriend(match[0].id);
    std::cout << "Friend " << name.toStdString() << " removed" << std::endl;
}

void Contacts::debug(QString s) const
{
    std::cout << "[DEBUG] : " << s.toStdString() << std::endl;
}