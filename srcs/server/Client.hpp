/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Client
*/

#pragma once
#include "../network/Socket.hpp"

namespace babel {

class Client {
	public:
		Client(std::unique_ptr<Socket> sock) : socket(std::move(sock)), _id(uid++) {};
		~Client() = default;

		auto getId() { return _id; };

        std::unique_ptr<Socket> socket;
	protected:
	private:
		int _id;

		static int uid;
};

}