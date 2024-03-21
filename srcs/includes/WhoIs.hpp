#pragma once

#include "User.hpp"
#include "Command.hpp"

class Command;

class	WhoIs : public Command
{
	public:
		WhoIs();
		~WhoIs();
		void	execute(usrsMap &users, chanMap &chan, int fd) const;
		void	sendWhoIs(User *client, User *whoUsr, chanMap &chan, int fd) const;
		User	*getUser(usrsMap &users, const std::string &name) const;
		bool	doesChanExist(chanMap &chan, std::string name) const;
		int		doesUserExist(usrsMap &usrs, std::string nick) const;
		std::string	getWhoIsChannelsBuffer(chanMap &chan, std::string nick) const;
		WhoIs	*clone() const;
};