#pragma once

#include "User.hpp"
#include "Command.hpp"
#include <fstream>

class Command;

class	Motd : public Command
{
	public:
		Motd();
		~Motd();
		void	execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const;
		bool	doesChanExist(std::map<std::string, Channel *> &chan, std::string name) const;
		int		doesUserExist(std::map<int, User *> &usrs, std::string nick) const;
		Motd	*clone() const;
};