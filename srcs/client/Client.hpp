/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Client
*/

#pragma once
#include "../network/Socket.hpp"

namespace babel {

class Client {
	public:
		Client()
        {
        }
		~Client() = default;

        void connect(std::string host, int port)
        {
            _sock.connect(host, port);
        }

        void run()
        {
            std::cout << _sock.receive(true) << std::endl;
            for (std::string line; std::getline(std::cin, line);) {
                std::cout << "Sending: " << line << std::endl;
                _sock.send(line);
            }
        }


	protected:
	private:
        Socket _sock;
};

}