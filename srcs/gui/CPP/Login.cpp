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

QString Login::connect(QString const &username, QString const &password, QString const &address)
{
    if (username == "")
        return "Username empty";
    if (password == "")
        return "Password empty";
    if (address == "")
        return "Hostname empty";
    auto client = Network::getInstance(address.toUtf8().constData())->getClient();
    try {
        client->updateServerInfos();
    } catch(...) {
        Network::resetInstance();
        return "connection to server failed";
    }
    try {
        client->signIn(username.toUtf8().constData(), password.toUtf8().constData());
    } catch(ClientFailedSign &e) {
        Network::resetInstance();
        return "Failed to login";
    }
    client->updateFriends();
    return "OK";
}

QString Login::signUp(QString const &username, QString const &password, QString const &address)
{
    if (username == "")
        return "Username empty";
    if (password == "")
        return "Password empty";
    if (address == "")
        return "Hostname empty";
    auto client = Network::getInstance(address.toUtf8().constData())->getClient();
    try {
        client->updateServerInfos();
    } catch(...) {
        Network::resetInstance();
        return "connection to server failed";
    }
    try {
        client->signUp(username.toUtf8().constData(), password.toUtf8().constData());
    } catch (ClientFailedSign &e) {
        Network::resetInstance();
        return "Failed to signup";
    }
    client->updateFriends();
    return "OK";
}

bool Login::logout()
{
    return true;
}
