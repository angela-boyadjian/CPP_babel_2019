/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Server
*/

#pragma once

#include <unordered_map>
#include <chrono>

#include "../Request.hpp"
#include "broadcast.hpp"
#include "../network/Socket.hpp"
#include "./Client.hpp"

namespace babel {

class Server {
	public:
		Server(int port, int udpport);
		~Server();

        using HandleFunction = RequestHandling *(Server::*)(Client &, Request &rq, RequestHandling *);

        void checkForNewClients();
        void receiveClientData();
        void receiveUdpPunch();
        void handleClientRequest(Client &client, Request *);
        void run();
        void handleBroadcastResponse(RequestHandling *handler);
        void sendRequest(Socket &sock, Request *request);

        RequestHandling *yaya(Client &client, Request &rq, RequestHandling *response);
        RequestHandling *connect(Client &client, Request &rq, RequestHandling *response);
        RequestHandling *disconnect(Client &client, Request &rq, RequestHandling *response);
        RequestHandling *registerClient(Client &client, Request &rq, RequestHandling *response);
        RequestHandling *handleMessage(Client &client, Request &rq, RequestHandling *response);
        RequestHandling *requestCall(Client &client, Request &rq, RequestHandling *response);
        RequestHandling *acceptCall(Client &client, Request &rq, RequestHandling *response);
        RequestHandling *denyCall(Client &client, Request &rq, RequestHandling *response);
        RequestHandling *addFriend(Client &client, Request &rq, RequestHandling *response);
        RequestHandling *removeFriend(Client &client, Request &rq, RequestHandling *response);
        RequestHandling *friendsList(Client &client, Request &rq, RequestHandling *response);
        RequestHandling *getClientFromName(Client &client, Request &rq, RequestHandling *response);
        RequestHandling *hangUp(Client &client, Request &rq, RequestHandling *response);

        struct Handler {
            bool needsLog;
            HandleFunction handler;
        };

	protected:
	private:
        Socket _sock;
        Socket _udpsock { Socket::Type::UDP };
        std::map<int, std::unique_ptr<Client>> _clients {};

        std::unordered_map<Request::Type, Handler> handlers {
            { Request::Type::CLIENT_CONNECT, { false, &Server::connect } },
            { Request::Type::CLIENT_REGISTER, { false, &Server::registerClient } },
            { Request::Type::MESSAGE, { true, &Server::handleMessage } },
            { Request::Type::ADD_FRIEND, { true, &Server::addFriend } },
            { Request::Type::REMOVE_FRIEND, { true, &Server::removeFriend } },
            { Request::Type::FRIENDS_LIST, { true, &Server::friendsList } },
            { Request::Type::CALL_REQUEST, { true, &Server::requestCall } },
            { Request::Type::CALL_ACCEPT, { true, &Server::acceptCall } },
            { Request::Type::CALL_DENY, { true, &Server::denyCall } },
            { Request::Type::GET_CLIENT_FROM_NAME, { false, &Server::getClientFromName } },
            { Request::Type::HANG_UP, { false, &Server::hangUp } }
        };
};

}