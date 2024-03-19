#pragma once

#include "User.hpp"
#include "Command.hpp"

class UserCmd : public Command
{
	public:
		UserCmd();
		~UserCmd();
		void	execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const;
		UserCmd	*clone() const;
		bool	doesNameExist(std::map<int, User *> userMap, std::string name) const;
		bool	doesChanExist(std::map<std::string, Channel *> &chan, std::string name) const;
		int		doesUserExist(std::map<int, User *> &usrs, std::string nick) const;
		bool	containsRestrictedChar(std::string name) const;
		std::vector<std::string>	parseParams(std::map<int, std::string> cmd, int fd, std::string nickname) const;
};