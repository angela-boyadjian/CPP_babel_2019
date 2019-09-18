/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Socket
*/

#include "Socket.hpp"

namespace babel {

Socket::Socket()
{
}

Socket::Socket(std::unique_ptr<protocol::socket> sock) : _sock(std::move(sock))
{
}

void Socket::connect(std::string host, int port)
{
    _resolver = std::make_unique<protocol::resolver>(_io_context);
    protocol::resolver::query query(host, std::to_string(port));
    auto endpoint = _resolver->resolve(query);
    _sock = std::make_unique<protocol::socket>(_io_context);
    boost::asio::connect(*_sock, endpoint);
}

void Socket::listen(int port)
{
    _acceptor = std::make_unique<protocol::acceptor>(_io_context, protocol::endpoint(protocol::v4(), port));
}

std::unique_ptr<Socket> Socket::accept(bool wait)
{
    if (_acceptor.get() == nullptr) { throw SocketInvalidState("You need to listen before accept"); }

    _acceptor->non_blocking(!wait);
    auto socket = std::make_unique<protocol::socket>(_io_context);

    try {
        _acceptor->accept(*socket);
    } catch (boost::system::system_error &e) {
        if (e.code() == boost::asio::error::would_block) return { nullptr };
        throw SocketException(e.what());
    }
    auto res = std::make_unique<Socket>(std::move(socket));
    return res;
}

std::string Socket::receive(bool wait)
{
    if (_sock.get() == nullptr) throw SocketInvalidState("Socket not initialized");

    _sock->non_blocking(!wait);

    boost::asio::mutable_buffer buffer;
    boost::system::error_code error;

    boost::array<char, 128> buf { 0 };
    size_t len = 0;
    try {
        len = _sock->read_some(boost::asio::buffer(buf));
    } catch(boost::system::system_error &e) {
        if (e.code() == boost::asio::error::would_block) return "";
        if (e.code() == boost::asio::error::eof) throw SocketConnectionClosed();
        throw SocketException(e.what());
    }
    return std::string(buf.data(), len);
}

void Socket::send(std::string data)
{
    if (_sock.get() == nullptr) throw SocketException("Can\'t send if socket have not been initialized");
    boost::asio::write(*_sock, boost::asio::buffer(data));
}

}