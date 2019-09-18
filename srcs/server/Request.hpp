/*
** EPITECH PROJECT, 2019
** babel
** File description:
** Request
*/

#pragma once

typedef unsigned int Port;

enum RequestType {
    CLIENT_CONNECTED,
    CLIENT_DISCONNECTED,
    MESSAGE,
    CALL_REQUEST,
    CALL_ACCEPT,
    CALL_DENY,
};

struct ClientInfos {
    char username[64];
    char password[64];
};

struct Message {
    int targetId;
    char message[256];
};

struct CallRequest {
    int targetId;
};

struct CallInfos {
    int targetId;
    char host[32];
    Port port;
};

union RequestData {
    ClientInfos connected;
    ClientInfos disconnected;
    Message message;
    CallInfos call;
};

struct Request {
    RequestType type;
    RequestData data;
};

enum BroadcastType {
    TO_ONE,
    TO_MANY,
    TO_ALL,
};

struct BroadcastToMany {
    int number;
    int targets[256];
};

union Target {
    int singleTarget;
    BroadcastToMany manyTargets;
};

struct RequestHandling {
    BroadcastType broadcastType;
    Target targetsinfos;
};

RequestHandling *handler(RequestHandling *response)
{
    response->broadcastType = TO_MANY;
    return nullptr;
}
