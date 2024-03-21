#pragma once

#include "User.hpp"
#include "Command.hpp"

class Command;

class	Part : public Command
{
	public:
		Part();
		~Part();
		void	execute(usrsMap &users, chanMap &chan, int fd) const;
		void	parseInput(strVector &chanVec, std::string &text, std::string param) const;
		strVector	parseChansToPart(const std::string &list) const;
		bool	doesChanExist(chanMap &chan, std::string name) const;
		int		doesUserExist(usrsMap &usrs, std::string nick) const;
		void	sendPart(strVector, std::string, User*, chanMap&, int) const;
		void	removeEmptyChannel(chanMap &chan, std::string name) const;
		Part	*clone() const;
};