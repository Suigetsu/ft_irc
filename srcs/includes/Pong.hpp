#pragma once

#include "User.hpp"
#include "Command.hpp"

class Command;

class	Pong : public Command
{
	public:
		Pong();
		~Pong();
		void	execute(usrsMap &users, chanMap &chan, int fd) const;
		bool	doesChanExist(chanMap &chan, std::string name) const;
		int		doesUserExist(usrsMap &usrs, std::string nick) const;
		Pong	*clone() const;
};