#pragma once

#include "User.hpp"
#include "Command.hpp"

class Command;

class	Invite : public Command
{
	public:
		Invite();
		~Invite();
		void	execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const;
		void	parseInput(std::vector<std::string> &parsedArgs, std::string param) const;
		bool	doesChanExist(std::map<std::string, Channel *> &chan, std::string name) const;
		int	doesUserExist(std::map<int, User *> &usrs, std::string nick) const;
		Invite	*clone() const;
};