#pragma once

#include "User.hpp"
#include "Command.hpp"

class Command;

class	Who : public Command
{
	public:
		Who();
		~Who();
		void	execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const;
		void	sendWho(User *usr, Channel *chan, int fd) const;
		Who	*clone() const;
};