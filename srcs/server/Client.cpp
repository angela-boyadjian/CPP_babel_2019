/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Client
*/

#include "Client.hpp"

namespace babel {

using namespace sqlite_orm;

int Client::uid = -1;

bool Client::registerClient(std::string name, std::string password)
{
    std::hash<std::string> hasher { };

    size_t hash = hasher(password);
    auto exists = database::Connector::get().get_all<database::Client>(where(c(&database::Client::name) == name));
    if (exists.size() > 0) {
        return false;
    }
    database::Client newInfos;
    newInfos.name = name;
    newInfos.password = hash;
    database::Connector::get().insert<database::Client>(newInfos);
    return true;
}

std::vector<database::Client> Client::getClientsFromName(std::string name)
{
    std::vector<database::Client> found { };

    auto cond = where(like(&database::Client::name, "%" + name + "%"));
    // TODO replace 5 by define
    auto results = database::Connector::get().get_all<database::Client>(cond, limit(5));
    for (auto &c : results) {
        found.push_back(c);
    }
    return found;
}

void Client::getFriends()
{
    auto friendsQuery = database::Connector::get()
        .select(columns(&database::Client::id, &database::Client::name, &database::Friends::owner, &database::Friends::target),
        inner_join<database::Client>(
            on(c(&database::Client::id) == &database::Friends::target)
        ),
        where(c(&database::Friends::owner) == infos.id)
    );
    std::vector<database::Client> friends { };
    std::cout << "Friends: " << friendsQuery.size() << std::endl;
    for (auto &c : friendsQuery) {
        friends.push_back({
            std::get<0>(c),
            std::get<1>(c),
            0,
        });
    }
    myFriends = friends;
}

bool Client::addFriend(int id, database::Client *newFriend)
{
    auto a = database::Connector::get().get_all<database::Friends>(
        sqlite_orm::where(c(&database::Friends::owner) == infos.id and c(&database::Friends::target) == id)
    );

    if (a.size() > 0) return false;
    database::Connector::get().insert<database::Friends>({
        infos.id,
        id
    });
    auto newFriendRequest = database::Connector::get().get_all<database::Client>(where(c(&database::Client::id) == id));
    *newFriend = newFriendRequest[0];
    return true;
}

bool Client::removeFriend(int id)
{
    try {
        database::Connector::get().remove_all<database::Friends>(where(c(&database::Friends::owner) == getId() && c(&database::Friends::target) == id));
        return true;
    } catch (...) {
        return false;
    }
}

bool Client::login(std::string name, std::string password)
{
    auto client = database::Connector::get().get_all<database::Client>(sqlite_orm::where(sqlite_orm::is_equal(&database::Client::name, name)));

    if (client.size() == 0) return false;
    // TODO hash password
    std::hash<std::string> hasher { };
    if (client[0].password == hasher(password)) {
        std::cout << "Getting friends !" << std::endl;
        infos.id = client[0].id;
        infos.name = client[0].name;
        getFriends();
        return true;
    }
    return false;
}

}
