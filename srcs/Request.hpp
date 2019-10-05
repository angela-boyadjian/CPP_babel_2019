/*
** EPITECH PROJECT, 2019
** babel
** File description:
** Request
*/

#pragma once

using Port = int;
using Id = int;

#define MAX_MESSAGE_LEN 255
#define MAX_NAME_LEN 63
#define MAX_PASSWORD_LEN MAX_NAME_LEN
#define MAX_AUTOCOMPLETE 5
#define UDP_PUNCH_SIZE 5

struct ClientInfos {
    char username[MAX_NAME_LEN + 1];
    char password[MAX_PASSWORD_LEN + 1];
};

struct Message {
    Id targetId;
    Id senderId;
    char message[MAX_MESSAGE_LEN + 1];
};

struct Friend {
    Id id;
    bool connected;
    char name[MAX_NAME_LEN + 1];
    unsigned int totalFriendNb;
};

struct CallInfos {
    Id targetId;
    Id callerId; // Filled only on client called
    char host[32];
    Port port;
};

struct PortIp {
    char ip[32];
    Port port;
};

struct FriendAutoComplete {
    Friend infos[MAX_AUTOCOMPLETE];
    size_t nb;
    char base[MAX_NAME_LEN + 1];
};

struct Target {
    int id;
};

class Request {
    public:
        enum class Type {
            UNKNOWN,
            SUCCESS,
            FAILURE,
            CLIENT_REGISTER,
            CLIENT_CONNECT,
            ADD_FRIEND,
            MESSAGE,
            CALL_REQUEST,
            CALL_ACCEPT,
            CALL_DENY,
            FRIEND_INFO,
            FRIENDS_LIST,
            REMOVE_FRIEND,
            GET_CLIENT_FROM_NAME,
            HANG_UP,
            UDP_PUNCH,
        };

        union Data {
            ClientInfos connectInfos;
            ClientInfos registerInfos;

            FriendAutoComplete autoComplete;

            Message message;
            CallInfos call;
            Friend addFriend;
            Target hangup;
            PortIp network;
        };

        Request(Type type = Type::UNKNOWN) : type(type) {};
        Request(Type type, Data data) : type(type), data(data) {};

        Type type;
        Data data {};
};
