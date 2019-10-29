/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Network
*/

#include "Network.hpp"

Network *Network::instance = nullptr;
int Network::_tcpport = 0;
int Network::_udpport = 0;

Network::Network(std::string const &ip)
{
    _client = new babel::Client();
    try {
        _client->connect(ip.c_str(), _tcpport, _udpport);
    } catch (SocketConnectionClosed &e) {
        std::cout << "Connection closed" << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return;
    }
}

void Network::setPorts(int tcpport, int udpport)
{
    _tcpport = tcpport;
    _udpport = udpport;
}

Network *Network::getInstance(std::string const &ip)
{
    if (instance == nullptr) {
        instance = new Network(ip);
    }
    return instance;
}

babel::Client *Network::getClient() const
{
    return _client;
}