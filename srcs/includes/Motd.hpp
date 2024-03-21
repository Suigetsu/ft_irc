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
		void	execute(usrsMap &users, chanMap &chan, int fd) const;
		bool	doesChanExist(chanMap &chan, std::string name) const;
		int		doesUserExist(usrsMap &usrs, std::string nick) const;
		Motd	*clone() const;
};