#pragma once

#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>
#include "User.hpp"
#include "Channel.hpp"
#include "RPL.hpp"
#include "ERR.hpp"

typedef std::map<int, User *> usrsMap;
typedef std::map<std::string, Channel *> chanMap;
typedef std::vector<std::string> strVector;

class	Command
{
	public:
		Command();
		virtual ~Command();
		virtual void	execute(usrsMap &users, chanMap &chan, int fd) const = 0;
		virtual Command	*clone() const = 0;
		virtual bool	doesChanExist(chanMap &chan, std::string name) const = 0;
		virtual int		doesUserExist(usrsMap &usrs, std::string nick) const = 0;
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