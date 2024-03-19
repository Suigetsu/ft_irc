#pragma once

#include "User.hpp"
#include "Command.hpp"

class Command;

class	WhoIs : public Command
{
	public:
		WhoIs();
		~WhoIs();
		void	execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const;
		void	sendWhoIs(User *client, User *whoUsr, std::map<std::string, Channel *> &chan, int fd) const;
		User	*getUser(std::map<int, User *> &users, const std::string &name) const;
		bool	doesChanExist(std::map<std::string, Channel *> &chan, std::string name) const;
		int		doesUserExist(std::map<int, User *> &usrs, std::string nick) const;
		std::string	getWhoIsChannelsBuffer(std::map<std::string, Channel *> &chan, std::string nick) const;
		WhoIs	*clone() const;
};