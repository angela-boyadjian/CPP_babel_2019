/*
** EPITECH PROJECT, 2019
** babel
** File description:
** Server
*/

#include "Server.hpp"

namespace babel {

Server::Server(int port)
{
    std::cout << "Server started at port " << port << std::endl;
    _sock.listen(port);
}

Server::~Server()
{
}

void Server::run()
{
    while (true) {
        checkForNewClients();
        receiveClientData();
    }
}

void Server::receiveClientData()
{
    for (auto it = _clients.begin(); it != _clients.end();) {
        auto &client = *it;
        try {
            auto data = client->socket->receive(false);
            if (data.size() != 0) {
                std::cout << "Client " << client->getId() << ": " << data << std::endl;
            }
            it++;
        } catch (SocketConnectionClosed &e) {
            std::cout << "Client " << client->getId() << ": disconnected" << std::endl;
            it = _clients.erase(it);
        }
    }
}

void Server::checkForNewClients()
{
    while (true) {
        auto clientSocket = _sock.accept(false);
        if (clientSocket.get() == nullptr) break;
        auto client = std::make_unique<Client>(std::move(clientSocket));
        client->socket->send("Hello new client " + std::to_string(client->getId()));
        _clients.push_back(std::move(client));
    }
}

}