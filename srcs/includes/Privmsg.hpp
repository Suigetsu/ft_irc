#pragma once

#include "User.hpp"
#include "Command.hpp"

class Command;

class	Privmsg : public Command
{
	public:
		Privmsg();
		~Privmsg();
		void	execute(usrsMap &users, chanMap &chan, int fd) const;
		void	parseInput(strVector &recipVec, std::string &text, std::string param) const;
		strVector	getRecipients(const std::string &list) const;
		void	sendMsg(usrsMap &, chanMap &, int, strVector, std::string) const;
		int	doesUserExist(usrsMap &usrs, std::string nick) const;
		bool	doesChanExist(chanMap &chan, std::string name) const;
		void	bufferizeChan(User *user, chanMap &chan, std::string recp, std::string text, int fd) const;
		void	bufferizeUser(User *user, usrsMap &users, std::string recp, std::string text, int fd) const;
		Privmsg	*clone() const;
};