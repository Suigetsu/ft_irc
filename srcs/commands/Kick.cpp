#include "../includes/Kick.hpp"

Kick::Kick() : Command::Command()
{
	
}

Kick::~Kick()
{

}

int	Kick::doesUserExist(std::map<int, User *> &usrs, std::string nick) const
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

bool	Kick::doesChanExist(std::map<std::string, Channel *> &chan, std::string name) const
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

std::vector<std::string>	Kick::parseNamesToKick(const std::string &list) const
{
	std::vector<std::string> chans;
	std::istringstream iss(list);
	std::string token;
	while (std::getline(iss, token, ','))
	{
		chans.push_back(token);
	}
	return (chans);
}

void	Kick::parseInput(std::vector<std::string> &namesVec, std::string &channel, std::string &reason, std::string param) const
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
}

void	Kick::removeEmptyChannel(std::map<std::string, Channel *> &chan, std::string name) const
{
	if (chan[name]->isChannelEmpty() == true)
	{
		delete chan[name];
		chan.erase(name);
	}
}

void	Kick::kickMembers(std::map<std::string, Channel *> &chan, std::map<int, User *> &users, std::string channel, std::vector<std::string> names, std::string reason, int fd) const
{
	std::string buffer;
	for (std::vector<std::string>::iterator it = names.begin(); it != names.end(); it++)
	{
		if (this->doesUserExist(users, *it) == -1)
		{
			buffer += ERR_NOSUCHNICK(users[fd]->getNickname(), *it);
			continue ;
		}
		else if (!chan[channel]->isWithinChannel(*it))
		{
			buffer += ERR_USERNOTINCHANNEL(users[fd]->getNickname(), *it, channel);
			continue ;
		}
		buffer += KICK(users[fd]->getNickname(), users[fd]->getUsername(), \
			users[fd]->getHost(), channel, *it, reason);
		chan[channel]->broadcastToMembers(KICK(users[fd]->getNickname(), \
			users[fd]->getUsername(), users[fd]->getHost(), channel, *it, reason));
		chan[channel]->removeUser(chan[channel]->getUser(*it));
	}
	send (fd, buffer.c_str(), buffer.length(), 0);
	this->removeEmptyChannel(chan, channel);
}

void	Kick::execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const
{
	std::string channel;
	std::string reason;
	std::vector<std::string> names;
	if (users[fd]->getCommand().size() < 2)
	{
		send (fd, ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).c_str(), \
			ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).length(), 0);
		throw (Kick::unknownCommandException());
	}
	this->parseInput(names, channel, reason, users[fd]->getCommand()[FIRST_PARAM]);
	if (names.empty())
	{
		send (fd, ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).c_str(), \
			ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).length(), 0);
		throw (Kick::unknownCommandException());
	}
	if (!this->doesChanExist(chan, channel))
	{
		send (fd, ERR_NOSUCHCHANNEL(users[fd]->getNickname(), channel).c_str(), \
			ERR_NOSUCHCHANNEL(users[fd]->getNickname(), channel).length(), 0);
		return ;
	}
	if (!chan[channel]->isOperator(users[fd]->getNickname()))
	{
		send (fd, ERR_CHANOPRIVSNEEDED(users[fd]->getNickname(), channel).c_str(), \
			ERR_CHANOPRIVSNEEDED(users[fd]->getNickname(), channel).length(), 0);
		return ;
	}
	this->kickMembers(chan, users, channel, names, reason, fd);
}

Kick	*Kick::clone() const
{
	return (new Kick);
}