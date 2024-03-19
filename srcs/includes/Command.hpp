#pragma once

#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>
#include "User.hpp"
#include "Channel.hpp"
#include "RPL.hpp"
#include "ERR.hpp"

class	Command
{
	public:
		Command();
		virtual ~Command();
		virtual void	execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const = 0;
		virtual Command	*clone() const = 0;
		virtual bool	doesChanExist(std::map<std::string, Channel *> &chan, std::string name) const = 0;
		virtual int		doesUserExist(std::map<int, User *> &usrs, std::string nick) const = 0;
		class	registrationException : public std::exception
		{
			public:
				const char *what() const throw();
		};
		class	unknownCommandException : public std::exception
		{
			public:
				const char *what() const throw();
		};
};