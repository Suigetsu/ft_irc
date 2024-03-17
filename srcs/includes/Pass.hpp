#pragma once

#include "User.hpp"
#include "Command.hpp"

class Command;

class	Pass : public Command
{
	public:
		Pass();
		~Pass();
		void	execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const;
		Pass	*clone() const;
};