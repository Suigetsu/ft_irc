#pragma once

#include "User.hpp"
#include "Command.hpp"

class UserCmd : public Command
{
	public:
		UserCmd();
		~UserCmd();
		void	execute(usrsMap &users, chanMap &chan, int fd) const;
		UserCmd	*clone() const;
		bool	doesNameExist(usrsMap userMap, std::string name) const;
		bool	doesChanExist(chanMap &chan, std::string name) const;
		int		doesUserExist(usrsMap &usrs, std::string nick) const;
		bool	containsRestrictedChar(std::string name) const;
		strVector	parseParams(std::map<int, std::string> cmd, int fd, std::string nickname) const;
};