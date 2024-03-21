#pragma once

#include "User.hpp"
#include "Command.hpp"

class Nick : public Command
{
	public:
		Nick();
		~Nick();
		void	execute(usrsMap &users, chanMap &chan, int fd) const;
		Nick	*clone() const;
		bool	doesNameExist(usrsMap userMap, std::string name) const;
		bool	doesChanExist(chanMap &chan, std::string name) const;
		int		doesUserExist(usrsMap &usrs, std::string nick) const;
		bool	containsRestrictedChar(std::string name) const;
};