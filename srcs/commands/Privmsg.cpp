#include "../includes/Privmsg.hpp"

Privmsg::Privmsg() : Command::Command()
{
	
}

Privmsg::~Privmsg()
{

}

strVector	Privmsg::getRecipients(const std::string &list) const
{
	strVector recipients;
	std::istringstream iss(list);
	std::string token;
	while (std::getline(iss, token, ','))
	{
		recipients.push_back(token);
	}
	return (recipients);
}

void	Privmsg::parseInput(strVector &recipVec, std::string &text, std::string param) const
{
	std::string recipients;
	if (param.find(" ") == std::string::npos)
	{
		recipVec.push_back(param.substr(0, param.find("\n")));
		return ;
	}
	recipients = param.substr(0, param.find(" "));
	param.erase(0, param.find(" ") + 1);
	text = param.substr(0, param.find("\n"));
	recipVec = this->getRecipients(recipients);
}

int	Privmsg::doesUserExist(usrsMap &usrs, std::string nick) const
{
	usrsMap::iterator it = usrs.begin();
	while (it != usrs.end())
	{
		if (it->second->getNick() == nick)
			return it->second->getFd();
		it++;
	}
	return -1;
}

bool	Privmsg::doesChanExist(chanMap &chan, std::string name) const
{
	chanMap::iterator it = chan.begin();
	while (it != chan.end())
	{
		if (it->second->getName() == name)
			return true;
		it++;
	}
	return false;
}

void	Privmsg::bufferizeChan(User *user, chanMap &chan, std::string recp, std::string text, int fd) const
{
	std::vector<User *> tmp;;
	if (this->doesChanExist(chan, recp) == false)
	{
		send (fd, ERR_NOSUCHCHANNEL(user->getNick(), recp).c_str(), \
			ERR_NOSUCHCHANNEL(user->getNick(), recp).length(), 0);
		return ;
	}
	tmp = chan[recp]->getUsers();
	if (chan[recp]->isWithinChannel(user->getNick()) == false)
	{
		send (fd, ERR_CANNOTSENDTOCHAN(user->getNick(), recp).c_str(), \
			ERR_CANNOTSENDTOCHAN(user->getNick(), recp).length(), 0);
		return ;
	}
	std::vector<User *>::iterator it = tmp.begin();
	while (it != tmp.end())
	{
		if ((*it)->getFd() != fd)
			send ((*it)->getFd(), PRIVMSG(user->getNick(), user->getName(), user->getHost(), recp, text).c_str(), \
				PRIVMSG(user->getNick(), user->getName(), user->getHost(), recp, text).length(), 0);
		it++;
	}
}

void	Privmsg::bufferizeUser(User *user, usrsMap &users, std::string recp, std::string text, int fd) const
{
	int recFd = this->doesUserExist(users, recp);
	if (recFd == -1)
	{
		send (fd, ERR_NOSUCHNICK(user->getNick(), recp).c_str(), \
			ERR_NOSUCHNICK(user->getNick(), recp).length(), 0);
		return ;
	}
	send (recFd, PRIVMSG(user->getNick(), user->getName(), user->getHost(), recp, text).c_str(), \
		PRIVMSG(user->getNick(), user->getName(), user->getHost(), recp, text).length(), 0);
}

void	Privmsg::sendMsg(usrsMap &usrs, chanMap &chan, int fd, strVector recp, std::string text) const
{
	strVector::iterator it = recp.begin();
	std::string buffer;
	while (it != recp.end())
	{
		if (it->find('#') == 0)
			this->bufferizeChan(usrs[fd], chan, *it, text, fd);
		else
			this->bufferizeUser(usrs[fd], usrs, *it, text, fd);
		it++;
	}
}

void	Privmsg::execute(usrsMap &users, chanMap &chan, int fd) const
{
	std::string text;
	strVector recip;
	if (users[fd]->getCommand().size() < 2)
	{
		send (fd, ERR_NORECIPIENT(users[fd]->getNick()).c_str(), \
			ERR_NORECIPIENT(users[fd]->getNick()).length(), 0);
		return ;
	}
	this->parseInput(recip, text, users[fd]->getCommand()[FIRST_PARAM]);
	if (text.empty())
	{
		send (fd, ERR_NOTEXTTOSEND(users[fd]->getNick()).c_str(), \
			ERR_NOTEXTTOSEND(users[fd]->getNick()).length(), 0);
		return ;
	}
	if (text.length() > 510)
	{
		send (fd, LONG_MESSAGE(users[fd]->getNick()).c_str(), \
			LONG_MESSAGE(users[fd]->getNick()).length(), 0);
		return ;
	}
	this->sendMsg(users, chan, fd, recip, text);
}

Privmsg	*Privmsg::clone() const
{
	return (new Privmsg);
}