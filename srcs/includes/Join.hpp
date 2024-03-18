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
		void	removeEmptyChannel(std::map<std::string, Channel *> &chan, std::string name) const;
		bool	doesChanExist(std::map<std::string, Channel *> &chan, std::string name) const;
		int		doesUserExist(std::map<int, User *> &usrs, std::string nick) const;
		void	leaveAllChan(std::map<std::string, Channel *> &chan, User *user) const;
		void	eraseChanMap(std::map<std::string, Channel *> &chan, std::vector<std::string> names) const;
		std::vector<std::string>	setChans(const std::string &list) const;
		std::vector<std::string>	setKeys(const std::string &list) const;
};