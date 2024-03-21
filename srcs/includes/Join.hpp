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
		void	execute(usrsMap &users, chanMap &chan, int fd) const;
		Join	*clone() const;
		bool	isNameValid(const std::string &name) const;
		void	parseChannels(strVector &chanVec, strVector &keyVec, std::string param) const;
		void	removeEmptyChannel(chanMap &chan, std::string name) const;
		bool	doesChanExist(chanMap &chan, std::string name) const;
		int		doesUserExist(usrsMap &usrs, std::string nick) const;
		void	leaveAllChan(chanMap &chan, User *user) const;
		void	eraseChanMap(chanMap &chan, strVector names) const;
		strVector	setChans(const std::string &list) const;
		strVector	setKeys(const std::string &list) const;
};