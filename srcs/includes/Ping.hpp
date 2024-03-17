#pragma once

#include "User.hpp"
#include "Pong.hpp"
#include "Command.hpp"

class Command;

class	Ping : public Command
{
	public:
		Ping();
		~Ping();
		void	execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const;
		Ping	*clone() const;
};