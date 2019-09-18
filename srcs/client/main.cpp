/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** main
*/

#include "./Client.hpp"

int main()
{
    babel::Client client;
    try {
        client.connect("localhost", 8000);
        client.run();
    } catch (SocketConnectionClosed &e) {
        std::cout << "Connection closed" << std::endl;
    }
    return 0;
}