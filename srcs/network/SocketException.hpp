/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** SocketException
*/

#ifndef SOCKETEXCEPTION_HPP_
#define SOCKETEXCEPTION_HPP_

#include <exception>
#include <string>

class SocketException : public std::exception
{
    public:
        SocketException(const std::string &error) : msg("[SOCKET]: " + error) {};
        ~SocketException() = default;
        virtual const char *what() const throw()
        {
            return msg.c_str();
        }
    protected:
        std::string msg;
};

class SocketConnectionClosed : public SocketException
{
    public:
        SocketConnectionClosed() : SocketException("Connection closed") {};
        ~SocketConnectionClosed() = default;
};

class SocketInvalidState : public SocketException
{
    public:
        SocketInvalidState(const std::string &error) : SocketException(error) {};
        ~SocketInvalidState() = default;
};

#endif /* !SOCKETEXCEPTION_HPP_ */
