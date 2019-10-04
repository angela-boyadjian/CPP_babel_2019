/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** main
*/

#include "./Client.hpp"

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: " << av[0] << " host" << std::endl;
        return 84;
    }
    babel::Client client;
    try {
        client.connect(av[1], 8000, 8001);
        client.run();
    } catch (SocketConnectionClosed &e) {
        std::cout << "Connection closed" << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}