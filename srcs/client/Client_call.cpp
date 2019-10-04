/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Call
*/

#include "Client.hpp"

namespace babel {

    static void udpPunch(Socket &sock, const std::string &host, int port, PortIp &portIp)
    {
        sock.connect(host, port);
        Request req(Request::Type::UDP_PUNCH);
        sock.send(&req, sizeof(req));
        sock.receive(&req, sizeof(req), true);
        strcpy(portIp.ip, req.data.network.ip);
        portIp.port = req.data.network.port;
    }

    void Client::call(int targetId)
    {
        _call = std::make_unique<Socket>(Socket::Type::UDP);
        _call->listen();

        // udp punching
        PortIp sockInfos {};
        udpPunch(*_call.get(), _host, _udpport, sockInfos);

        std::cout << "External ip(" << sockInfos.ip << ") port(" << sockInfos.port << ")" << std::endl;
        Request::Data data;
        data.call.targetId = targetId;
        data.call.port = sockInfos.port;
        strcpy(data.call.host, sockInfos.ip);

        _callerId = targetId;

        Request req(Request::Type::CALL_REQUEST, data);
        std::cout << "Requesting a call..." << std::endl;
        _server.send(&req, sizeof(req));
    }

    void Client::callRequest(Request &req)
    {
        // TODO handle better if client already in call
        std::cout << "Call request: ";
        if (_callbackCall == nullptr || _callbackCall(req.data.call.callerId) == true) { // if client accept
            std::cout << "Accepted" << std::endl;

            _call = std::make_unique<Socket>(Socket::Type::UDP);
            _call->listen();

            PortIp sockInfos {};
            udpPunch(*_call.get(), _host, _udpport, sockInfos);

            std::cout << "Connecting to ip(" << req.data.call.host << ") port(" << req.data.call.port << ")" << std::endl;
            _call->connect(req.data.call.host, req.data.call.port);

            _callerId = req.data.call.callerId;

            _audio = std::make_unique<AudioModule>(*_call.get());
            _audio->start();

            req.type = Request::Type::CALL_ACCEPT;
            req.data.call.port = sockInfos.port;
            strcpy(req.data.call.host, sockInfos.ip);
        } else {
            std::cout << "Deny" << std::endl;
            req.type = Request::Type::CALL_DENY;
        }
        _server.send(&req, sizeof(Request));
    }

    void Client::callAccept(Request &req)
    {
        std::cout << "Call accepted" << std::endl;
        std::cout << "Connecting to ip(" << req.data.call.host << ") port(" << req.data.call.port << ")" << std::endl;
        _call->connect(req.data.call.host, req.data.call.port);
        _audio = std::make_unique<AudioModule>(*_call.get());
        _audio->start();
    }

    void Client::callDeny(Request &req)
    {
        std::cout << "Call deny" << std::endl;
        _call.reset();
    }

    void Client::stopCall()
    {
        Request req(Request::Type::HANG_UP);
        req.data.hangup.id = _callerId;
        _server.send(&req, sizeof(Request));
        _stopCall();
    }

    void Client::_stopCallRequest(Request &req)
    {
        _stopCall();
    }

    void Client::_stopCall()
    {
        _call.reset();
        _audio.reset();
        _callerId = 0;
    }

    void Client::setCallCallback(callback_call_fct cb)
    {
        _callbackCall = cb;
    }

}