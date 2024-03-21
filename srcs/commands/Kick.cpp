#include "../includes/Kick.hpp"

Kick::Kick() : Command::Command()
{
	
}

Kick::~Kick()
{

}

int	Kick::doesUserExist(usrsMap &usrs, std::string nick) const
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

bool	Kick::doesChanExist(chanMap &chan, std::string name) const
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

strVector	Kick::parseNamesToKick(const std::string &list) const
{
	strVector chans;
	std::istringstream iss(list);
	std::string token;
	while (std::getline(iss, token, ','))
	{
		chans.push_back(token);
	}
	return (chans);
}

void	Kick::parseInput(strVector &namesVec, std::string &channel, std::string &reason, std::string param) const
{
	std::string names;
	if (param.find(" ") == std::string::npos)
	{
		channel = param;
		return ;
	}
	channel = param.substr(0, param.find(" "));
	param.erase(0, param.find(" ") + 1);
	if (param.find(" ") != std::string::npos)
	{
		names = param.substr(0, param.find(" "));
		param.erase(0, param.find(" ") + 1);
		reason = param;
	}
	else
	{
		names = param.substr(0, param.find("\n"));
		reason = PART_MSG;
	}
	namesVec = this->parseNamesToKick(names);
	if (reason.length() > 255)
		reason = PART_MSG;
}

void	Kick::removeEmptyChannel(chanMap &chan, std::string name) const
{
	if (chan[name]->isChannelEmpty() == true)
	{
		delete chan[name];
		chan.erase(name);
	}
}

void	Kick::kickMembers(chanMap &chan, usrsMap &users, std::string channel, strVector names, std::string reason, int fd) const
{
	std::string buffer;
	for (strVector::iterator it = names.begin(); it != names.end(); it++)
	{
		if (this->doesUserExist(users, *it) == -1)
		{
			buffer += ERR_NOSUCHNICK(users[fd]->getNick(), *it);
			continue ;
		}
		else if (!chan[channel]->isWithinChannel(*it))
		{
			buffer += ERR_USERNOTINCHANNEL(users[fd]->getNick(), *it, channel);
			continue ;
		}
		buffer += KICK(users[fd]->getNick(), users[fd]->getName(), \
			users[fd]->getHost(), channel, *it, reason);
		chan[channel]->broadcastToMembers(KICK(users[fd]->getNick(), \
			users[fd]->getName(), users[fd]->getHost(), channel, *it, reason));
		chan[channel]->removeUser(chan[channel]->getUser(*it));
	}
	this->removeEmptyChannel(chan, channel);
}

void	Kick::execute(usrsMap &users, chanMap &chan, int fd) const
{
	std::string channel;
	std::string reason;
	strVector names;
	if (users[fd]->getCommand().size() < 2)
	{
		send (fd, ERR_NEEDMOREPARAMS(users[fd]->getNick(), users[fd]->getCommand()[COMMAND]).c_str(), \
			ERR_NEEDMOREPARAMS(users[fd]->getNick(), users[fd]->getCommand()[COMMAND]).length(), 0);
		return ;
	}
	this->parseInput(names, channel, reason, users[fd]->getCommand()[FIRST_PARAM]);
	if (names.empty())
	{
		send (fd, ERR_NEEDMOREPARAMS(users[fd]->getNick(), users[fd]->getCommand()[COMMAND]).c_str(), \
			ERR_NEEDMOREPARAMS(users[fd]->getNick(), users[fd]->getCommand()[COMMAND]).length(), 0);
		return ;
	}
	if (!this->doesChanExist(chan, channel))
	{
		send (fd, ERR_NOSUCHCHANNEL(users[fd]->getNick(), channel).c_str(), \
			ERR_NOSUCHCHANNEL(users[fd]->getNick(), channel).length(), 0);
		return ;
	}
	if (!chan[channel]->isOperator(users[fd]->getNick()))
	{
		send (fd, ERR_CHANOPRIVSNEEDED(users[fd]->getNick(), channel).c_str(), \
			ERR_CHANOPRIVSNEEDED(users[fd]->getNick(), channel).length(), 0);
		return ;
	}
	this->kickMembers(chan, users, channel, names, reason, fd);
}

Kick	*Kick::clone() const
{
	return (new Kick);
}