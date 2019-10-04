/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Client
*/

#include "Client.hpp"

namespace babel {

    void Client::connect(const std::string &host, int port, int udpport)
    {
        std::cout << "Connecting to server..." << std::endl;
        _server.connect(host, port);
        char data[256] {0};
        _server.receive(data, 255, true);
        std::cout << std::string(data, 256) << std::endl;
        _udpport = udpport;
        _host = host;
    }

    void Client::sendMessage(std::string msg_str, int targetId)
    {
        if (msg_str.size() > MAX_MESSAGE_LEN) {
            throw ClientInvalidParameter("Message is too long");
        }

        Request::Data data;
        data.message.targetId = targetId;
        strcpy(data.message.message, msg_str.c_str());
        const Request req(Request::Type::MESSAGE, data);
        _server.send(&req, sizeof(Request));
    }

    void Client::messageReceive(Request &res)
    {
        auto msg_str = res.data.message.message;
        std::string msg(msg_str, strlen(msg_str));
        int from = res.data.message.targetId;

        std::cout << "Received a message from " << from << ": " << msg << std::endl;
    }

    void Client::signIn(const std::string &username, const std::string &password)
    {
        _sign(Request::Type::CLIENT_CONNECT, username, password);
    }

    void Client::signUp(const std::string &username, const std::string &password)
    {
        _sign(Request::Type::CLIENT_REGISTER, username, password);
        signIn(username, password);
    }

    void Client::_sign(Request::Type type, const std::string &username, const std::string &password)
    {
        if (username.length() > MAX_NAME_LEN || password.length() > MAX_PASSWORD_LEN)
            throw ClientInvalidParameter("Username or password are too long");

        Request req(type);
        strcpy(req.data.registerInfos.username, username.c_str());
        strcpy(req.data.registerInfos.password, password.c_str());
        _server.send(&req, sizeof(Request));
        req = _waitServerRequest({ Request::Type::SUCCESS, Request::Type::FAILURE });
        if (req.type == Request::Type::FAILURE)
            throw ClientFailedSign();
    }

    Client::callbackId Client::addCallback(Request::Type type, callback_fct cb)
    {
        CallbackInfo cbInfos {};
        cbInfos.id = ++_ucallbackid;
        cbInfos.fct = cb;
        _callbacks[type].push_back(cbInfos);
        return cbInfos.id;
    }

    void Client::removeCallback(callbackId id)
    {
        for (auto & [_, cbVec] : _callbacks)
        {
            std::remove_if(cbVec.begin(), cbVec.end(), [id](auto info) { return info.id == id; });
        }
    }

    Request Client::_receiveRequest(Socket &sock, bool wait)
    {
        Request req {};
        auto len = sock.receive(&req, sizeof(Request), wait);

        return req;
    }

    void Client::_handleRequest(Request &req)
    {
        auto it = handlers.find(req.type);
        if (it == handlers.end()) throw ClientInvalidParameter("Invalid request type");
        auto handler = (*it).second;
        (this->*(handler))(req);
        for (auto &cbInfo: _callbacks[req.type])
        {
            cbInfo.fct(req);
        }
    }

    Request Client::_waitServerRequest(std::vector<Request::Type> types)
    {
        while (true) {
            auto req = _receiveRequest(_server, true);
            auto it = std::find(types.begin(), types.end(), req.type);
            if (it == types.end()) {
                _handleRequest(req);
            } else {
                return req;
            }
        }
    }

    void Client::updateServerInfos()
    {
        while (true) {
            auto req = _receiveRequest(_server, false);
            if (req.type == Request::Type::UNKNOWN) {
                break;
            }
            _handleRequest(req);
        }
    }

    void Client::handleInput(std::string &line, int &targetId)
    {
        std::istringstream iss(line);
        std::vector<std::string> args((std::istream_iterator<std::string>(iss)),
            std::istream_iterator<std::string>());

        if (args[0] == "call") {
            call(targetId);
        } else if (args[0] == "target") {
            targetId = std::atoi(args[1].c_str());
        } else if (args[0] == "friends") {
            if (args[1] == "update") {
                updateFriends();
            } else if (args[1] == "add") {
                addFriend(std::atoi(args[2].c_str()));
            } else if (args[1] == "remove") {
                removeFriend(std::atoi(args[2].c_str()));
            } else if (args[1] == "autocomplete") {
                auto friends = autocompleteFriends(args[2].c_str());
                for (auto f : friends) {
                    std::cout << f.name << ": " << f.id << std::endl;
                }
            } else {
                std::cout << "friends [remove, update, add, autocomplete] $id" << std::endl;
            }
        } else if (args[0] == "msg") {
            sendMessage(args[1], targetId);
        } else if (args[0] == "signin") {
            signIn(args[1], args[2]);
        } else if (args[0] == "signup") {
            signUp(args[1], args[2]);
        } else {
            std::cout << "Available command:" << std::endl
                << "\tmsg $message" << std::endl
                << "\t[signin, signup] $username $password" << std::endl
                << "\tfriends [add, remove, update, autocomplete] $id" << std::endl
                << "\tcall" << std::endl
                << "\ttarget $id" << std::endl;
        }
    }

    std::string getLine()
    {
        std::string line;
        do {
        std::getline(std::cin, line);
        } while (line.size() == 0);
        return line;
    }

    void Client::run()
    {
        int targetId = -1;
        std::future<std::string> input = std::async(getLine);
        std::cout << "Enter 'target $ID' to change your target" << std::endl;
        while (true) {
            if (input.wait_for(std::chrono::milliseconds(10)) == std::future_status::ready) {
                auto line = input.get();
                handleInput(line, targetId);
                input = std::async(getLine);
            }
            updateServerInfos();
        }
    }
}