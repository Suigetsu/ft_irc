#pragma once

#include "User.hpp"
#include "Command.hpp"

class Command;

class	Invite : public Command
{
	public:
		Invite();
		~Invite();
		void	execute(usrsMap &users, chanMap &chan, int fd) const;
		void	parseInput(strVector &parsedArgs, std::string param) const;
		bool	doesChanExist(chanMap &chan, std::string name) const;
		int	doesUserExist(usrsMap &usrs, std::string nick) const;
		Invite	*clone() const;
};