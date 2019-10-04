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
		babel::Client *getClient() const;
		// void changePort(std::string const &); // TODO Implement (settings)
	private:
        static Network *instance;
		babel::Client *_client;
		Network(std::string const & = "");
};
