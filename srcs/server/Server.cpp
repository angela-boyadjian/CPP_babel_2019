/*
** EPITECH PROJECT, 2019
** babel
** File description:
** Server
*/

#include "Server.hpp"

namespace babel {

Server::Server(int port, int udpport)
{
    _sock.listen(port);
    std::cout << "Server started on port " << port << std::endl;
    _udpsock.listen(udpport);
    std::cout << "Udp port on " << udpport << std::endl;
}

Server::~Server()
{
}

void Server::run()
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    while (true) {
        start = std::chrono::system_clock::now();
        checkForNewClients();
        receiveClientData();
        receiveUdpPunch();
        end = std::chrono::system_clock::now();
        int elapsed = std::chrono::duration_cast<std::chrono::microseconds>
            (end-start).count();
        if (elapsed < 1000) {
            std::this_thread::sleep_for(std::chrono::microseconds(1000 - elapsed));
        }
    }
}

void Server::receiveUdpPunch()
{
    Request req { };
    boost::asio::ip::udp::endpoint sender;
    auto res = _udpsock.receive(&req, sizeof(Request), false, &sender);
    if (res > 0) {
        strcpy(req.data.network.ip, sender.address().to_string().c_str());
        req.data.network.port = sender.port();
        _udpsock.send(&req, sizeof(Request), &sender);
    }
}

RequestHandling *Server::yaya(Client &client, Request &rq, RequestHandling *response)
{
    std::cout << "Not bound handler" << std::endl;
    return nullptr;
}

RequestHandling *Server::hangUp(Client &client, Request &rq, RequestHandling *response)
{
    response->response.type = Request::Type::HANG_UP;
    response->broadcastType = BroadcastType::TO_MANY;
    response->targetsinfos.manyTargets.number = 2;
    response->targetsinfos.manyTargets.targets[0] = rq.data.hangup.id;
    response->targetsinfos.manyTargets.targets[1] = client.getId();

    return response;
}

RequestHandling *Server::getClientFromName(Client &client, Request &rq, RequestHandling *response)
{
    response->response.type = Request::Type::GET_CLIENT_FROM_NAME;
    response->broadcastType = BroadcastType::TO_ONE;
    response->targetsinfos.singleTarget = client.getId();

    auto results = client.getClientsFromName(std::string(rq.data.autoComplete.base));
    response->response.data.autoComplete.nb = results.size();
    for (int i = 0; i < results.size(); i++) {
        response->response.data.autoComplete.infos[i].id = results[i].id;
        strcpy(response->response.data.autoComplete.infos[i].name, results[i].name.c_str());
    }
    return response;
}

RequestHandling *Server::requestCall(Client &client, Request &rq, RequestHandling *response)
{
    response->broadcastType = BroadcastType::TO_ONE;
    response->targetsinfos.singleTarget = rq.data.call.targetId;
    response->response.type = Request::Type::CALL_REQUEST;
    response->response.data.call.callerId = client.getId();
    response->response.data.call.targetId = rq.data.call.targetId;

    auto clientInfos = client.socket->getInfos(false);

    strcpy(response->response.data.call.host, rq.data.call.host);
    response->response.data.call.port = rq.data.call.port;

    // strcpy(response->response.data.call.host, clientInfos.host.c_str());
    // response->response.data.call.port = rq.data.call.port;

    // TODO fill host and port
    return response;
}

RequestHandling *Server::connect(Client &client, Request &rq, RequestHandling *response)
{
    response->broadcastType = BroadcastType::TO_ONE;
    int oldId = client.getId();

    if (client.login(rq.data.connectInfos.username, rq.data.connectInfos.password)) {
        client.logged = true;
        std::cout << "Client '" << client.infos.name << "' (" << client.getId() << ") logged !" << std::endl;;
        auto old = _clients.extract(oldId);
        old.key() = client.getId();
        _clients.insert(std::move(old));
        response->targetsinfos.singleTarget = client.getId();
        response->response.type = Request::Type::SUCCESS;
    } else {
        response->targetsinfos.singleTarget = oldId;
        response->response.type = Request::Type::FAILURE;
        client.logged = false;
    }
    return response;
}

RequestHandling *Server::disconnect(Client &client, Request &rq, RequestHandling *response)
{
    client.logged = false;
    return nullptr;
}

RequestHandling *Server::registerClient(Client &client, Request &rq, RequestHandling *response)
{
    response->broadcastType = BroadcastType::TO_ONE;
    response->targetsinfos.singleTarget = client.getId();
    if (client.registerClient(rq.data.registerInfos.username, rq.data.registerInfos.password)) {
        response->response.type = Request::Type::SUCCESS;
    } else {
        response->response.type = Request::Type::FAILURE;
    }
    return response;
}

RequestHandling *Server::acceptCall(Client &client, Request &rq, RequestHandling *response)
{
    response->broadcastType = BroadcastType::TO_ONE;
    response->targetsinfos.singleTarget = rq.data.call.callerId;
    response->response.type = Request::Type::CALL_ACCEPT;
    response->response.data.call.callerId = rq.data.call.callerId;
    response->response.data.call.targetId = rq.data.call.targetId;

    auto clientInfos = client.socket->getInfos(false);

    strcpy(response->response.data.call.host, rq.data.call.host);
    response->response.data.call.port = rq.data.call.port;

    // strcpy(response->response.data.call.host, clientInfos.host.c_str());
    // response->response.data.call.port = rq.data.call.port;

    // TODO fill host and port of the client given in parameter
    return response;
}

RequestHandling *Server::denyCall(Client &client, Request &rq, RequestHandling *response)
{
    response->broadcastType = BroadcastType::TO_ONE;
    response->targetsinfos.singleTarget = rq.data.call.callerId;
    response->response.type = Request::Type::CALL_DENY;
    response->response.data.call.callerId = rq.data.call.callerId;
    response->response.data.call.targetId = rq.data.call.targetId;

    return response;
}

RequestHandling *Server::handleMessage(Client &client, Request &rq, RequestHandling *handler)
{
    handler->broadcastType = TO_ONE;
    handler->targetsinfos.singleTarget = rq.data.message.targetId;
    handler->response.type = Request::Type::MESSAGE;
    strcpy(handler->response.data.message.message, rq.data.message.message);
    return handler;
}

RequestHandling *Server::addFriend(Client &client, Request &rq, RequestHandling *response)
{
    database::Client newFriend { };
    response->broadcastType = TO_ONE;
    response->targetsinfos.singleTarget = client.getId();
    response->response.type = Request::Type::FAILURE;
    if (client.addFriend(rq.data.addFriend.id, &newFriend)) {
        response->response.type = Request::Type::FRIEND_INFO;
        response->response.data.addFriend.id = newFriend.id;
        strcpy(response->response.data.addFriend.name, newFriend.name.c_str());
    }
    return response;
}

RequestHandling *Server::friendsList(Client &client, Request &rq, RequestHandling *response)
{
    response->broadcastType = TO_ONE;
    response->targetsinfos.singleTarget = client.getId();
    response->response.type = Request::Type::FRIEND_INFO;
    client.getFriends();

    for (auto &c : client.myFriends) {
        response->response.data.addFriend.totalFriendNb = client.myFriends.size();
        response->response.data.addFriend.id = c.id;
        response->response.data.addFriend.connected = _clients.find(c.id) != _clients.end();
        strcpy(response->response.data.addFriend.name, c.name.c_str());
        sendRequest(*client.socket, &response->response);
    }
    return nullptr;
}


void Server::sendRequest(Socket &sock, Request *request)
{
    sock.send(request, sizeof(Request));
}

void Server::handleBroadcastResponse(RequestHandling *handler)
{
    if (handler->broadcastType == TO_ONE) {
        auto client = _clients.find(handler->targetsinfos.singleTarget);
        if (client == _clients.end()) return;
        this->sendRequest(*client->second->socket, &handler->response);
    } else if (handler->broadcastType == TO_MANY) {
        for (int i = 0; i < handler->targetsinfos.manyTargets.number; i++) {
            auto client = _clients.find(handler->targetsinfos.manyTargets.targets[i]);
            if (client == _clients.end()) return;
            this->sendRequest(*client->second->socket, &handler->response);
        }
    } else {
        for (auto &it : _clients) {
            this->sendRequest(*it.second.get()->socket, &handler->response);
        }
    }
}

void Server::handleClientRequest(Client &client, Request *rq)
{
    std::cout << "Client " << client.getId() << ": " << (int) rq->type << std::endl;
    RequestHandling handling { };
    auto handler = this->handlers.find(rq->type);
    if (handler == this->handlers.end()) return;
    if (handler->second.needsLog && !client.logged) {
        std::cout << "Not logged" << std::endl;
        handling.response.type = Request::Type::FAILURE;
        sendRequest(*client.socket, &handling.response);
        return;
    }
    RequestHandling *returnHandler = (this->*(handler->second.handler))(client, *rq, &handling);
    if (returnHandler == nullptr) return;
    this->handleBroadcastResponse(returnHandler);
}

void Server::receiveClientData()
{
    for (auto it = _clients.begin(); it != _clients.end();) {
        auto &client = it->second;
        Request rq { };
        try {
            size_t received = client->socket->receive(&rq, sizeof(Request), false);
            if (received > 0) {
                handleClientRequest(*client, &rq);
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
        std::string hello = "Hello new client " + std::to_string(client->getId());
        std::cout << "From address: '" << client->socket->getInfos(false).host << "' and port: '" << client->socket->getInfos(false).port << "'" << std::endl;
        client->socket->send(hello.c_str(), hello.size());
        _clients[client->getId()] = std::move(client);
    }
}

}