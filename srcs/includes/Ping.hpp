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
		void	execute(usrsMap &users, chanMap &chan, int fd) const;
		bool	doesChanExist(chanMap &chan, std::string name) const;
		int		doesUserExist(usrsMap &usrs, std::string nick) const;
		Ping	*clone() const;
};