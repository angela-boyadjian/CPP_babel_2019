/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Client
*/

#pragma once

#include <unordered_map>
#include <future>
#include <thread>
#include <chrono>

#include "../network/Socket.hpp"
#include "../Request.hpp"
#include "./AudioModule.hpp"
#include "./Client_exception.hpp"

namespace babel {

class Client {
        using callback_fct = std::function<void(Request &req)>;
        using callback_call_fct = std::function<bool(int callerId)>;
        using callbackId = int;

	public:
		Client() = default;
		~Client() = default;

        void connect(const std::string &host, int port, int udpport);
        void run();

        void call(int targetId);
        void stopCall();

        //TODO call hangup cb accept/refuse call

        void sendMessage(std::string msg_str, int targetId);

        void removeFriend(int targetId);
        void addFriend(Id id);
        std::vector<Friend> autocompleteFriends(const std::string &base);
        void updateFriends();

        void signIn(const std::string &username, const std::string &password);
        void signUp(const std::string &username, const std::string &password);

        const std::vector<Friend> &getFriends() const { return _friends; };

        void handleInput(std::string &line, int &targetId);

        void updateServerInfos();


        callbackId addCallback(Request::Type type, callback_fct cb);
        void removeCallback(callbackId id);
        void setCallCallback(callback_call_fct cb);

	private:

        struct CallbackInfo {
                callbackId id;
                callback_fct fct;
        };
        std::unordered_map<Request::Type, std::vector<CallbackInfo>> _callbacks {};

        void _sign(Request::Type type, const std::string &username, const std::string &password);
        void _handleRequest(Request &req);
        Request _receiveRequest(Socket &sock, bool wait=false);
        Request _waitServerRequest(std::vector<Request::Type> types);
        void updateFriend(Request &req);
        void _stopCallRequest(Request &req);
        void _stopCall();
        void _removeFriend(int target);
        void _removeFriend(Request &req);

        void callRequest(Request &req);
        void callAccept(Request &req);
        void callDeny(Request &req);
        void messageReceive(Request &res);

        Socket _server { Socket::Type::TCP };
        std::unique_ptr<Socket> _call;
        Id _callerId { 0 };
        int _udpport {0};
        std::string _host;
        std::vector<Friend> _friends;
        std::unique_ptr<AudioModule> _audio;
        callbackId _ucallbackid { 0 };
        callback_call_fct _callbackCall { nullptr };

        std::unordered_map<Request::Type, void (Client::*)(Request &req)> handlers {
            { Request::Type::CALL_REQUEST, &Client::callRequest },
            { Request::Type::CALL_DENY, &Client::callDeny  },
            { Request::Type::CALL_ACCEPT, &Client::callAccept },
            { Request::Type::MESSAGE, &Client::messageReceive },
            { Request::Type::FRIEND_INFO, &Client::updateFriend },
            { Request::Type::HANG_UP, &Client::_stopCallRequest },
            { Request::Type::REMOVE_FRIEND, &Client::_removeFriend },
        };
};

}