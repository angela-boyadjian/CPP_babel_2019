/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Login
*/

#include "Login.hpp"
#include "Network.hpp"

#include <iostream>
#include <string>

Login::Login(QObject *parent) :
    QObject(parent)
{
}

Q_INVOKABLE bool Login::sign(QString const &username, QString const &password, QString const &address) const
{
    auto client = Network::getInstance(address.toUtf8().constData())->getClient();
    try {
        std::cout << "try to log" << std::endl;
        client->signIn(username.toUtf8().constData(), password.toUtf8().constData());
    } catch(ClientFailedSign &e) {
        try {
            std::cout << "try to register" << std::endl;
            client->signUp(username.toUtf8().constData(), password.toUtf8().constData());
        } catch (ClientFailedSign &e) {
            return false;
        }
    }
    client->updateFriends();
    std::cout << "logged" << std::endl;
    return true;
}