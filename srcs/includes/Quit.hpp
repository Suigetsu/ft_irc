#pragma once

#include "User.hpp"
#include "Command.hpp"
#include <unistd.h>
#include "Server.hpp"

class Command;

class	Quit : public Command
{
	public:
		Quit();
		~Quit();
		void	execute(usrsMap &users, chanMap &chan, int fd) const;
		bool	doesChanExist(chanMap &chan, std::string name) const;
		int		doesUserExist(usrsMap &usrs, std::string nick) const;
		void	leaveAllChannels(usrsMap &users, chanMap &chan,  std::string reason,int fd) const;
		void	removeEmptyChannel(chanMap &chan, std::string name) const;
		void	eraseChanMap(chanMap &chan, strVector names) const;
		Quit	*clone() const;
};