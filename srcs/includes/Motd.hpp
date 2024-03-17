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
		Motd	*clone() const;
};