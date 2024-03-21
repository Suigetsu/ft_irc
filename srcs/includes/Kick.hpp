#pragma once

#include "User.hpp"
#include "Command.hpp"

class Command;

class	Kick : public Command
{
	public:
		Kick();
		~Kick();
		void	execute(usrsMap &users, chanMap &chan, int fd) const;
		strVector	parseNamesToKick(const std::string &list) const;
		bool	doesChanExist(chanMap &chan, std::string name) const;
		int		doesUserExist(usrsMap &usrs, std::string nick) const;
		void	parseInput(strVector &namesVec, std::string &channel, std::string &reason, std::string param) const;
		void	removeEmptyChannel(chanMap &chan, std::string name) const;
		void	kickMembers(chanMap &chan, usrsMap &users, std::string channel, strVector names, std::string reason, int fd) const;
		Kick	*clone() const;
};
