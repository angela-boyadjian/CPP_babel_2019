/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Client_exception
*/

#pragma once

#include <exception>
#include <string>

class ClientException : public std::exception
{
    public:
        ClientException(const std::string &error) : msg("[CLIENT]: " + error) {};
        ~ClientException() = default;
        virtual const char *what() const throw()
        {
            return msg.c_str();
        }
    protected:
        std::string msg;
};

class ClientInvalidParameter : public ClientException
{
    public:
        ClientInvalidParameter(const std::string &error) : ClientException(error) {};
        ClientInvalidParameter() : ClientException("Given parameters are invalid") {};
        ~ClientInvalidParameter() = default;
};

class ClientFailedSign : public ClientException
{
    public:
        ClientFailedSign() : ClientException("Failed to sign in or sign up") {};
        ~ClientFailedSign() = default;
};
