#include "../includes/Notice.hpp"

Notice::Notice() : Command::Command()
{
	
}

Notice::~Notice()
{

}

strVector	Notice::getRecipients(const std::string &list) const
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

void	Notice::parseInput(strVector &recipVec, std::string &text, std::string param) const
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

int	Notice::doesUserExist(usrsMap &usrs, std::string nick) const
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

bool	Notice::doesChanExist(chanMap &chan, std::string name) const
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

void	Notice::bufferizeChan(User *user, chanMap &chan, std::string recp, std::string text, int fd) const
{
	if (this->doesChanExist(chan, recp) == false)
		return ;
	if (chan[recp]->isWithinChannel(user->getNick()) == true)
	{
        std::vector<User *>::iterator it = chan[recp]->getUsers().begin();
        while (it != chan[recp]->getUsers().end())
        {
            if ((*it)->getFd() != fd)
                send ((*it)->getFd(), NOTICE(user->getNick(), user->getName(), user->getHost(), recp, text).c_str(), \
                    NOTICE(user->getNick(), user->getName(), user->getHost(), recp, text).length(), 0);
            it++;
        }
	}
}

void	Notice::bufferizeUser(User *user, usrsMap &users, std::string recp, std::string text) const
{
	int recFd = this->doesUserExist(users, recp);
	if (recFd != -1)
	    send (recFd, NOTICE(user->getNick(), user->getName(), user->getHost(), recp, text).c_str(), \
		    NOTICE(user->getNick(), user->getName(), user->getHost(), recp, text).length(), 0);
}

void	Notice::sendMsg(usrsMap &usrs, chanMap &chan, int fd, strVector recp, std::string text) const
{
	strVector::iterator it = recp.begin();
	std::string buffer;
	while (it != recp.end())
	{
		if (it->find('#') == 0)
			this->bufferizeChan(usrs[fd], chan, *it, text, fd);
		else
			this->bufferizeUser(usrs[fd], usrs, *it, text);
		it++;
	}
}

void	Notice::execute(usrsMap &users, chanMap &chan, int fd) const
{
	std::string text;
	strVector recip;
	if (users[fd]->getCommand().size() < 2)
		return ;
	this->parseInput(recip, text, users[fd]->getCommand()[FIRST_PARAM]);
	if (text.empty())
		return ;
	this->sendMsg(users, chan, fd, recip, text);
}

Notice	*Notice::clone() const
{
	return (new Notice);
}