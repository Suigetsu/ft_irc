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
		void	execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const;
		bool	doesChanExist(std::map<std::string, Channel *> &chan, std::string name) const;
		int		doesUserExist(std::map<int, User *> &usrs, std::string nick) const;
		void	leaveAllChannels(std::map<int, User *> &users, std::map<std::string, Channel *> &chan,  std::string reason,int fd) const;
		void	removeEmptyChannel(std::map<std::string, Channel *> &chan, std::string name) const;
		void	eraseChanMap(std::map<std::string, Channel *> &chan, std::vector<std::string> names) const;
		Quit	*clone() const;
};