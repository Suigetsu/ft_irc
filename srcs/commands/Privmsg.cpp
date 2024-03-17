#include "../includes/Privmsg.hpp"

Privmsg::Privmsg() : Command::Command()
{
	
}

Privmsg::~Privmsg()
{

}

std::vector<std::string>	Privmsg::getRecipients(const std::string &list) const
{
	std::vector<std::string> recipients;
	std::istringstream iss(list);
	std::string token;
	while (std::getline(iss, token, ','))
	{
		recipients.push_back(token);
	}
	return (recipients);
}

void	Privmsg::parseInput(std::vector<std::string> &recipVec, std::string &text, std::string param) const
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

int	Privmsg::doesUserExist(std::map<int, User *> &usrs, std::string nick) const
{
	std::map<int, User *>::iterator it = usrs.begin();
	while (it != usrs.end())
	{
		if (it->second->getNickname() == nick)
			return it->second->getFd();
		it++;
	}
	return -1;
}

bool	Privmsg::doesChanExist(std::map<std::string, Channel *> &chan, std::string name) const
{
	std::map<std::string, Channel *>::iterator it = chan.begin();
	while (it != chan.end())
	{
		if (it->second->getName() == name)
			return true;
		it++;
	}
	return false;
}

void	Privmsg::bufferizeChan(User *user, std::map<std::string, Channel *> &chan, std::string recp, std::string text, int fd) const
{
	std::vector<User *> tmp;;
	if (this->doesChanExist(chan, recp) == false)
	{
		send (fd, ERR_NOSUCHCHANNEL(user->getNickname(), recp).c_str(), \
			ERR_NOSUCHCHANNEL(user->getNickname(), recp).length(), 0);
		return ;
	}
	tmp = chan[recp]->getUsers();
	if (chan[recp]->isWithinChannel(user->getNickname()) == false)
	{
		send (fd, ERR_CANNOTSENDTOCHAN(user->getNickname(), recp).c_str(), \
			ERR_CANNOTSENDTOCHAN(user->getNickname(), recp).length(), 0);
		return ;
	}
	std::vector<User *>::iterator it = tmp.begin();
	while (it != tmp.end())
	{
		if ((*it)->getFd() != fd)
			send ((*it)->getFd(), PRIVMSG(user->getNickname(), user->getUsername(), user->getHost(), recp, text).c_str(), \
				PRIVMSG(user->getNickname(), user->getUsername(), user->getHost(), recp, text).length(), 0);
		it++;
	}
}

void	Privmsg::bufferizeUser(User *user, std::map<int, User *> &users, std::string recp, std::string text, int fd) const
{
	int recFd = this->doesUserExist(users, recp);
	if (recFd == -1)
	{
		send (fd, ERR_NOSUCHNICK(user->getNickname(), recp).c_str(), \
			ERR_NOSUCHNICK(user->getNickname(), recp).length(), 0);
		return ;
	}
	send (recFd, PRIVMSG(user->getNickname(), user->getUsername(), user->getHost(), recp, text).c_str(), \
		PRIVMSG(user->getNickname(), user->getUsername(), user->getHost(), recp, text).length(), 0);
}

void	Privmsg::sendMsg(std::map<int, User *> &usrs, std::map<std::string, Channel *> &chan, int fd, std::vector<std::string> recp, std::string text) const
{
	std::vector<std::string>::iterator it = recp.begin();
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

void	Privmsg::execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const
{
	std::string text;
	std::vector<std::string> recip;
	if (users[fd]->getCommand().size() < 2)
	{
		send (fd, ERR_NORECIPIENT(users[fd]->getNickname()).c_str(), \
			ERR_NORECIPIENT(users[fd]->getNickname()).length(), 0);
		return ;
	}
	this->parseInput(recip, text, users[fd]->getCommand()[FIRST_PARAM]);
	if (text.empty())
	{
		send (fd, ERR_NOTEXTTOSEND(users[fd]->getNickname()).c_str(), \
			ERR_NOTEXTTOSEND(users[fd]->getNickname()).length(), 0);
		return ;
	}
	this->sendMsg(users, chan, fd, recip, text);
}

Privmsg	*Privmsg::clone() const
{
	return (new Privmsg);
}