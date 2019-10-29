/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Args
*/

#pragma once

#include <exception>
#include <string>
#include <iostream>
#include <algorithm>

class ArgsException : public std::exception
{
    public:
        ArgsException(const std::string &error) : msg("[ARGS]: " + error) {};
        ~ArgsException() = default;
        virtual const char *what() const throw()
        {
            return msg.c_str();
        }
    protected:
        std::string msg;
};

class ArgsHelp : public ArgsException
{
    public:
        ArgsHelp() : ArgsException("help requested") {};
        ~ArgsHelp() = default;
};

class ArgsInvalidArgument : public ArgsException
{
    public:
        ArgsInvalidArgument(const std::string &error) : ArgsException(error) {};
        ~ArgsInvalidArgument() = default;
};

class Args {
	public:
		Args(int ac, char **av) : udpport(8001), tcpport(8000)
        {
            if (ac < 0) return;
            progname = av[0];
            for (int i = 1; i < ac; i++) {
                auto arg = std::string(av[i]);
                if (arg == "--help" || arg == "-h") {
                    _printHelp();
                    throw ArgsHelp();
                }
                if (arg != "-u" && arg != "-t") throw ArgsInvalidArgument("Invalid argument: " + arg);
                if (i + 1 > ac) throw ArgsInvalidArgument("Missing the port");
                if (!_is_number(av[i + 1])) throw ArgsInvalidArgument("Port must be positive a number");
                auto nb = atoi(av[i + 1]);
                if (arg == "-u") udpport = nb;
                if (arg == "-t") tcpport = nb;
                i += 1;
            }
        }
		~Args() = default;

        std::string progname;
        int udpport;
        int tcpport;

	protected:
	private:
        void _printHelp() {
            std::cout << progname << " -u $udpport -t $tcpport" << std::endl;
            std::cout << "\t-u, Udp port to use for udppunch" << std::endl;
            std::cout << "\t-t, Tcp port to use to listen" << std::endl;
        }

        bool _is_number(const std::string& s)
        {
            return !s.empty() && std::find_if(s.begin(),
                s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
        }
};
