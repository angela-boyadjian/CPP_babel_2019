/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Socket
*/

#include "Socket.hpp"

Socket::Socket(Type type) : _type(type)
{
}

Socket::Socket(std::unique_ptr<tcp::socket> sock) : _sock_tcp(std::move(sock)), _type(Type::TCP)
{
}

Socket::Socket(std::unique_ptr<udp::socket> sock) : _sock_udp(std::move(sock)), _type(Type::UDP)
{
}

void Socket::connect(std::string host, int port)
{
    if (_type == Type::TCP) {
        tcp::resolver resolver { _io_context };
        tcp::resolver::query query(host, std::to_string(port));
        auto endpoint = resolver.resolve(query);
        _sock_tcp = std::make_unique<tcp::socket>(_io_context);
        boost::asio::connect(*_sock_tcp, endpoint);
    } else { // UDP
        udp::resolver resolver(_io_context);
        _dest_endpoint = std::make_unique<udp::endpoint>(
            *resolver.resolve(udp::v4(), host, std::to_string(port)).begin()
        );
    }
}

void Socket::listen(int port)
{
    if (_type == Type::TCP) {
        _acceptor = std::make_unique<tcp::acceptor>(_io_context, tcp::endpoint(tcp::v4(), port));
    } else {
        _sock_udp = std::make_unique<udp::socket>(_io_context, udp::endpoint(udp::v4(), port));
    }
}

std::unique_ptr<Socket> Socket::accept(bool wait)
{
    if (_type == Type::UDP) { throw SocketInvalidState("Can t accept with an udp socket"); }
    if (_acceptor.get() == nullptr) { throw SocketInvalidState("You need to listen before accept"); }

    _acceptor->non_blocking(!wait);
    auto socket = std::make_unique<tcp::socket>(_io_context);

    try {
        _acceptor->accept(*socket);
    } catch (boost::system::system_error &e) {
        if (e.code() == boost::asio::error::would_block) return { nullptr };
        throw SocketException(e.what());
    }
    auto res = std::make_unique<Socket>(std::move(socket));
    return res;
}

size_t Socket::receive(void *dest, size_t size, bool wait, udp::endpoint *sender_endpoint)
{
    if (_sock_tcp.get() == nullptr && _sock_udp.get() == nullptr) throw SocketInvalidState("Socket not initialized");

    if (_type == Type::UDP) _sock_udp->non_blocking(!wait);
    if (_type == Type::TCP) _sock_tcp->non_blocking(!wait);

    size_t len = 0;
    try {
        if (_type == Type::TCP) {
            len = _sock_tcp->read_some(boost::asio::buffer(dest, size));
        } else {
            udp::endpoint tmp;
            if (sender_endpoint == nullptr) sender_endpoint = &tmp;
            len = _sock_udp->receive_from(boost::asio::buffer(dest, size), *sender_endpoint);
            // TODO filter sender_endpoint == _dest_endpoint
        }
    } catch(boost::system::system_error &e) {
        if (e.code() == boost::asio::error::would_block) return 0;
        if (e.code() == boost::asio::error::eof || e.code() == boost::asio::error::connection_reset) throw SocketConnectionClosed();
        throw SocketException(e.what());
    }
    return len;
}

void Socket::send(const void *data, size_t size, udp::endpoint *dest_endpoint)
{
    if (_sock_tcp.get() == nullptr && _sock_udp.get() == nullptr) throw SocketInvalidState("Can\'t send if socket have not been initialized");
    if (dest_endpoint == nullptr) dest_endpoint = _dest_endpoint.get();

    if (_type == Type::TCP) {
        boost::asio::write(*_sock_tcp, boost::asio::buffer(data, size));
    } else {
        if (dest_endpoint == nullptr) throw SocketInvalidState("Can t send in udp if no connect() had been made");
        _sock_udp->send_to(boost::asio::buffer(data, size), *dest_endpoint);
    }
}

void Socket::clear()
{
    char buff[256] = { 0 };
    while (receive(buff, 256, false) == 256) {};
}

Socket::Infos Socket::getInfos(bool local)
{
    if (_type == Type::TCP) {
        auto info = local ? _sock_tcp->local_endpoint() : _sock_tcp->remote_endpoint();
        return { info.address().to_string(), info.port() };
    } else {
        auto info = local ? _sock_udp->local_endpoint() : _sock_udp->remote_endpoint();
        return { info.address().to_string(), info.port() };
    }
}
