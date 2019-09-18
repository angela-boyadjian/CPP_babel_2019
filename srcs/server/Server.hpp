/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Server
*/

#pragma once

#include <unordered_map>

#include "Request.hpp"
#include "../network/Socket.hpp"
#include "./Client.hpp"

namespace babel {

class Server {
	public:
		Server(int port);
		~Server();

        void checkForNewClients();
        void receiveClientData();
        void run();

        RequestHandling *yaya(RequestHandling *response);

	protected:
	private:
        Socket _sock;
        std::vector<std::unique_ptr<Client>> _clients {};

        std::unordered_map<RequestType, RequestHandling *(Server::*)(RequestHandling *)> map {};
};

}