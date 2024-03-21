#pragma once

#include "User.hpp"
#include "Command.hpp"

class Command;

class	Who : public Command
{
	public:
		Who();
		~Who();
		void	execute(usrsMap &users, chanMap &chan, int fd) const;
		void	sendWho(User *usr, Channel *chan, int fd) const;
		bool	doesChanExist(chanMap &chan, std::string name) const;
		int		doesUserExist(usrsMap &usrs, std::string nick) const;
		Who	*clone() const;
};