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

using tcp = boost::asio::ip::tcp;
using udp = boost::asio::ip::udp;

class Socket {
	public:
		struct Infos {
			std::string host;
			int port;
		};

		enum class Type {
			UDP,
			TCP
		};

		Socket(Type type=Type::TCP);
		Socket(std::unique_ptr<tcp::socket> sock);
		Socket(std::unique_ptr<udp::socket> sock);
		~Socket() = default;

		void listen(int port=0); // port 0 mean random port assignation for udp
		std::unique_ptr<Socket> accept(bool wait=false);
		void send(const void *, size_t size, udp::endpoint *dest_endpoint=nullptr);
        size_t receive(void *dest, size_t size, bool wait=false, udp::endpoint *sender_endpoint=nullptr);
		void connect(std::string host, int port);

		Infos getInfos(bool local);

	protected:
	private:

		Type _type;

		boost::asio::io_context _io_context;
		std::unique_ptr<tcp::socket> _sock_tcp { nullptr };
		std::unique_ptr<udp::socket> _sock_udp { nullptr };

		std::unique_ptr<tcp::acceptor> _acceptor { nullptr };

		std::unique_ptr<udp::endpoint> _dest_endpoint;
};
