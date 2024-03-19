#pragma once

#include "User.hpp"
#include "Command.hpp"

class Command;

class	Kick : public Command
{
	public:
		Kick();
		~Kick();
		void	execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const;
		std::vector<std::string>	parseNamesToKick(const std::string &list) const;
		bool	doesChanExist(std::map<std::string, Channel *> &chan, std::string name) const;
		int		doesUserExist(std::map<int, User *> &usrs, std::string nick) const;
		void	parseInput(std::vector<std::string> &namesVec, std::string &channel, std::string &reason, std::string param) const;
		void	removeEmptyChannel(std::map<std::string, Channel *> &chan, std::string name) const;
		void	kickMembers(std::map<std::string, Channel *> &chan, std::map<int, User *> &users, std::string channel, std::vector<std::string> names, std::string reason, int fd) const;
		Kick	*clone() const;
};
