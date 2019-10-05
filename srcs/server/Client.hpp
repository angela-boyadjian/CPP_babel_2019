/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Client
*/

#pragma once

#include "../network/Socket.hpp"
#include "sql/Database.hpp"
#include "sql/Connector.hpp"

namespace babel {

using Friends = std::vector<database::Client>;

class Client {
	public:

		Client(std::unique_ptr<Socket> sock) : socket(std::move(sock)), id(uid--)
			{};
		~Client() = default;

		database::Client infos { };

		auto getId() { return logged ? infos.id : id; };

		void getFriends();

		bool registerClient(std::string name, std::string password);
		bool login(std::string name, std::string password);
		bool addFriend(int id, database::Client *newFriend);
		bool removeFriend(int id);
		std::vector<database::Client> getClientsFromName(std::string name);

        std::unique_ptr<Socket> socket;
		int id;
		bool logged { false };
		Friends myFriends;
	protected:
	private:
		static int uid;
};

}
