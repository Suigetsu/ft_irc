#pragma once

#include "User.hpp"
#include "Command.hpp"

class Command;

class	Topic : public Command
{
	public:
		Topic();
		~Topic();
		void	execute(usrsMap &users, chanMap &chan, int fd) const;
		strVector parseTopic(std::string command) const;
		void	sendTopic(Channel *chan, User *user, int fd) const;
		void	setTopic(User *user, Channel **chan, std::string topic, int fd) const;
		bool	doesChanExist(chanMap &chan, std::string name) const;
		int		doesUserExist(usrsMap &usrs, std::string nick) const;
		Topic	*clone() const;
};