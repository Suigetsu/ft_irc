#pragma once

#include "User.hpp"
#include "Command.hpp"

class Command;

class	Part : public Command
{
	public:
		Part();
		~Part();
		void	execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const;
		void	parseInput(std::vector<std::string> &chanVec, std::string &text, std::string param) const;
		std::vector<std::string>	parseChansToPart(const std::string &list) const;
		bool	doesChanExist(std::map<std::string, Channel *> &chan, std::string name) const;
		int		doesUserExist(std::map<int, User *> &usrs, std::string nick) const;
		void	sendPart(std::vector<std::string>, std::string, User*, std::map<std::string, Channel *>&, int) const;
		void	removeEmptyChannel(std::map<std::string, Channel *> &chan, std::string name) const;
		Part	*clone() const;
};