/*
** EPITECH PROJECT, 2019
** babel
** File description:
** Database
*/

#pragma once

#include <string>
#include <memory>
namespace babel {
namespace database {

struct Client {
    int id;
    std::string name;
    size_t password;
};

struct Message {
    std::unique_ptr<int> owner_id;
    std::string content;
};

struct Friends { // Both are client IDs
    int owner;
    int target;
};

}
}
