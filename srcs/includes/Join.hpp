#pragma once

#include "User.hpp"
#include "Command.hpp"
#include "Channel.hpp"
#include <string>
#include <iostream>

class Command;

class	Join : public Command
{
	public:
		Join();
		~Join();
		void	execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const;
		Join	*clone() const;
		bool	isNameValid(const std::string &name) const;
		void	parseChannels(std::vector<std::string> &chanVec, std::vector<std::string> &keyVec, std::string param) const;
		std::vector<std::string>	setChans(const std::string &list) const;
		std::vector<std::string>	setKeys(const std::string &list) const;
};