/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** ASocket
*/

#pragma once

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <memory>
#include "SocketException.hpp"

namespace babel {

class Socket {
	using protocol = boost::asio::ip::tcp;

	public:
		Socket();
		Socket(std::unique_ptr<protocol::socket> sock);
		~Socket() = default;

		void listen(int port);
		std::unique_ptr<Socket> accept(bool wait=false);
        std::string receive(bool wait=false);
		void send(std::string);
		void connect(std::string host, int port);

	protected:
	private:

		boost::asio::io_context _io_context;
		std::unique_ptr<protocol::socket> _sock { nullptr };
		std::unique_ptr<protocol::acceptor> _acceptor { nullptr };
		std::unique_ptr<protocol::resolver> _resolver { nullptr };
};

}