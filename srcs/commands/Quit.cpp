#include "../includes/Quit.hpp"

Quit::Quit() : Command::Command()
{
	
}

Quit::~Quit()
{

}

int	Quit::doesUserExist(usrsMap &usrs, std::string nick) const
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

bool	Quit::doesChanExist(chanMap &chan, std::string name) const
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

void	Quit::removeEmptyChannel(chanMap &chan, std::string name) const
{
	if (chan[name]->isChannelEmpty() == true)
		delete chan[name];
}

void	Quit::eraseChanMap(chanMap &chan, strVector names) const
{
	strVector::iterator it = names.begin();
	while (it != names.end())
	{
		chan.erase(*it);
		it++;
	}
}

void	Quit::leaveAllChannels(usrsMap &users, chanMap &chan, std::string reason, int fd) const
{
	strVector	emptyChans;
	for (chanMap::iterator it = chan.begin(); it != chan.end(); it++)
	{
		if (!it->second->isWithinChannel(users[fd]->getNick()))
			continue ;
		if (it->second->isOperator(users[fd]->getNick()))
			it->second->unsetOperator(users[fd]);
		it->second->broadcastToMembers(QUIT_MSG(users[fd]->getNick(), \
			users[fd]->getName(), users[fd]->getHost(), reason));
		it->second->removeUser(users[fd]);
		if (it->second->isChannelEmpty())
		{
			this->removeEmptyChannel(chan, it->second->getName());
			emptyChans.push_back(it->second->getName());
		}
	}
	this->eraseChanMap(chan, emptyChans);
}

void	Quit::execute(usrsMap &users, chanMap &chan, int fd) const
{
	(void)chan;
	std::string reason;
	if (users[fd]->getCommand().size() == 1)
		reason = PART_MSG;
	else
		reason = users[fd]->getCommand()[FIRST_PARAM];
	send(fd, QUIT_MSG(users[fd]->getNick(),users[fd]->getName(),users[fd]->getHost(), reason).c_str(), \
		QUIT_MSG(users[fd]->getNick(),users[fd]->getName(),users[fd]->getHost(), reason).length(), 0);
	this->leaveAllChannels(users, chan, reason, fd);
	Server::QuitStatus = true;
}

Quit	*Quit::clone() const
{
	return (new Quit);
}