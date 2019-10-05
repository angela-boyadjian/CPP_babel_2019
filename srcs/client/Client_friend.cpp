/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Client_friend
*/

#include "Client.hpp"

namespace babel {

    void Client::updateFriend(Request &req)
    {
        auto id = req.data.addFriend.id;
        auto it = std::find_if(_friends.begin(), _friends.end(), [id](auto f){ return f.id == id; });
        if (it == _friends.end()) {
            // std::cout << "New friend " << req.data.addFriend.id << ": " << req.data.addFriend.name << std::endl;
            _friends.push_back(req.data.addFriend);
        } else {
           strcpy((*it).name, req.data.addFriend.name);
        }
    }

    void Client::updateFriends()
    {
        Request req(Request::Type::FRIENDS_LIST);
        _server.send(&req, sizeof(req));
    }

    void Client::removeFriend(int targetId)
    {
        Request req(Request::Type::REMOVE_FRIEND);
        req.data.addFriend.id = targetId;
        _server.send(&req, sizeof(Request));
        _removeFriend(targetId);
    }

    void Client::_removeFriend(int target)
    {
        auto it = std::find_if(_friends.begin(), _friends.end(), [target](auto f){ return f.id == target; });
        if (it != _friends.end()) _friends.erase(it);
    }

    void Client::_removeFriend(Request &req)
    {
        _removeFriend(req.data.addFriend.id);
    }

    void Client::addFriend(Id id)
    {
        std::cout << "Adding " << id << std::endl;
        Request req(Request::Type::ADD_FRIEND);
        req.data.addFriend.id = id;
        _server.send(&req, sizeof(Request));
    }

    std::vector<Friend> Client::autocompleteFriends(const std::string &base)
    {
        if (base.size() > MAX_NAME_LEN) throw ClientInvalidParameter();
        Request req(Request::Type::GET_CLIENT_FROM_NAME);
        strcpy(req.data.autoComplete.base, base.c_str());
        _server.send(&req, sizeof(Request));
        req = _waitServerRequest({ Request::Type::GET_CLIENT_FROM_NAME });
        std::vector<Friend> result {};
        for (auto i = 0; i < req.data.autoComplete.nb; i++) {
            result.push_back(req.data.autoComplete.infos[i]);
        }
        return result;
    }

}