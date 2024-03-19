#include "../includes/Quit.hpp"

Quit::Quit() : Command::Command()
{
	
}

Quit::~Quit()
{

}

int	Quit::doesUserExist(std::map<int, User *> &usrs, std::string nick) const
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

bool	Quit::doesChanExist(std::map<std::string, Channel *> &chan, std::string name) const
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

void	Quit::removeEmptyChannel(std::map<std::string, Channel *> &chan, std::string name) const
{
	if (chan[name]->isChannelEmpty() == true)
		delete chan[name];
}

void	Quit::eraseChanMap(std::map<std::string, Channel *> &chan, std::vector<std::string> names) const
{
	std::vector<std::string>::iterator it = names.begin();
	while (it != names.end())
	{
		chan.erase(*it);
		it++;
	}
}

void	Quit::leaveAllChannels(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, std::string reason, int fd) const
{
	std::vector<std::string> emptyChans;
	// (void) reason;
	for (std::map<std::string, Channel *>::iterator it = chan.begin(); it != chan.end(); it++)
	{
		if (!it->second->isWithinChannel(users[fd]->getNickname()))
			continue ;
		if (it->second->isOperator(users[fd]->getNickname()))
			it->second->unsetOperator(users[fd]);
		it->second->broadcastToMembers(QUIT_MSG(users[fd]->getNickname(), \
			users[fd]->getUsername(), users[fd]->getHost(), reason));
		it->second->removeUser(users[fd]);
		if (it->second->isChannelEmpty())
		{
			this->removeEmptyChannel(chan, it->second->getName());
			emptyChans.push_back(it->second->getName());
		}
	}
	this->eraseChanMap(chan, emptyChans);
}

void	Quit::execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const
{
	(void)chan;
	std::string reason;
	if (users[fd]->getCommand().size() == 1)
		reason = PART_MSG;
	else
		reason = users[fd]->getCommand()[FIRST_PARAM];
	send(fd, QUIT_MSG(users[fd]->getNickname(),users[fd]->getUsername(),users[fd]->getHost(), reason).c_str(), \
		QUIT_MSG(users[fd]->getNickname(),users[fd]->getUsername(),users[fd]->getHost(), reason).length(), 0);
	this->leaveAllChannels(users, chan, reason, fd);
	Server::QuitStatus = true;
}

Quit	*Quit::clone() const
{
	return (new Quit);
}