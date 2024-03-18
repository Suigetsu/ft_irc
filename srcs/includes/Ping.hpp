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
		bool	doesChanExist(std::map<std::string, Channel *> &chan, std::string name) const;
		int		doesUserExist(std::map<int, User *> &usrs, std::string nick) const;
		Ping	*clone() const;
};