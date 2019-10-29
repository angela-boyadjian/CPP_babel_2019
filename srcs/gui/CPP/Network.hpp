/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Network
*/

#pragma once

#include "../../client/Client.hpp"

class Network {
	public:
        static Network *getInstance(std::string const & = "");
		static void resetInstance() { instance = nullptr; }
		babel::Client *getClient() const;
		static void setPorts(int tcpport, int udpport);
	private:
        static Network *instance;
		static int _udpport;
		static int _tcpport;
		babel::Client *_client;
		Network(std::string const & = "");
};
