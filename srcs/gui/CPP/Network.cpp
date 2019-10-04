/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Network
*/

#include "Network.hpp"

Network *Network::instance = nullptr;

Network::Network(std::string const &ip)
{
    _client = new babel::Client();
    try {
        _client->connect(ip.c_str(), 8000, 8001);
    } catch (SocketConnectionClosed &e) {
        std::cout << "Connection closed" << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return;
    }
}

Network *Network::getInstance(std::string const &ip)
{
    if (instance == nullptr)
        instance = new Network(ip);
    return instance;
}

babel::Client *Network::getClient() const
{
    return _client;
}