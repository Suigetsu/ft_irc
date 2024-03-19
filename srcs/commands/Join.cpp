#include "../includes/Join.hpp"

Join::Join() : Command::Command()
{
	
}

Join::~Join()
{

}

std::vector<std::string>	Join::setChans(const std::string &list) const
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

std::vector<std::string>	Join::setKeys(const std::string &list) const
{
	std::vector<std::string> keys;
	std::istringstream iss(list);
	std::string token;
	while (std::getline(iss, token, ','))
	{
		keys.push_back(token);
	}
	return (keys);
}

void	Join::parseChannels(std::vector<std::string> &chanVec, std::vector<std::string> &keyVec, std::string param) const
{
	std::string chans;
	std::string keys;
	if (param.find(" ") != std::string::npos)
	{
		chans = param.substr(0, param.find(" "));
		param.erase(0, param.find(" ") + 1);
		keys = param.substr(0, param.find("\r"));
	}
	else
		chans = param.substr(0, param.find("\r"));
	chanVec = setChans(chans);
	keyVec = setKeys(keys);
}

int	Join::doesUserExist(std::map<int, User *> &usrs, std::string nick) const
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

bool	Join::doesChanExist(std::map<std::string, Channel *> &chan, std::string name) const
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

void	Join::removeEmptyChannel(std::map<std::string, Channel *> &chan, std::string name) const
{
	if (chan[name]->isChannelEmpty() == true)
		delete chan[name];
}

void	Join::eraseChanMap(std::map<std::string, Channel *> &chan, std::vector<std::string> names) const
{
	std::vector<std::string>::iterator it = names.begin();
	while (it != names.end())
	{
		chan.erase(*it);
		it++;
	}
}

void	Join::leaveAllChan(std::map<std::string, Channel *> &chan, User *user) const
{
	if (chan.size() < 1)
		return ;
	std::string buffer;
	std::vector<std::string> chanNames;
	std::map<std::string, Channel *>::iterator it = chan.begin();
	while (it != chan.end())
	{
		if (it->second->isWithinChannel(user->getNickname()))
		{
			buffer += PART(user->getNickname(), user->getUsername(), \
				user->getHost(), it->second->getName(), PART_MSG);
			it->second->broadcastToMembers(PART(user->getNickname(), user->getUsername(), \
				user->getHost(), it->second->getName(), PART_MSG));
			it->second->removeUser(user);
			if (it->second->isChannelEmpty())
			{
				chanNames.push_back(it->second->getName());
				this->removeEmptyChannel(chan, it->second->getName());
			}
		}
		it++;
	}
	this->eraseChanMap(chan, chanNames);
	send (user->getFd(), buffer.c_str(), buffer.length(), 0);
}

void	Join::execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const
{
	std::vector<std::string> chanVec;
	std::vector<std::string> keyVec;
	if (users[fd]->getCommand().size() < 2)
	{
		send (fd, ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).c_str(), \
		ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).length(), 0);
		throw (Join::unknownCommandException());
	}
	this->parseChannels(chanVec, keyVec, users[fd]->getCommand()[FIRST_PARAM]);
	for (size_t i = 0; i < chanVec.size(); i++)
	{
		if (!this->isNameValid(chanVec[i]) || chanVec[i].length() > 50)
		{
			send(fd, ERR_NOSUCHCHANNEL(users[fd]->getNickname(), chanVec[i]).c_str(), \
				ERR_NOSUCHCHANNEL(users[fd]->getNickname(), chanVec[i]).length(), 0);
			chanVec.erase(chanVec.begin() + i);
			if (i < keyVec.size())
				keyVec.erase(keyVec.begin() + i);
			continue ;
		}
		if (chanVec[i] == "0")
			this->leaveAllChan(chan, users[fd]);
		else if (this->doesChanExist(chan, chanVec[i]) == false)
		{
			chan[chanVec[i]] = new Channel(chanVec[i]);
			chan[chanVec[i]]->createChannel(users, fd);
		}
		else
		{
			if (i < keyVec.size())
				chan[chanVec[i]]->joinChannel(users, fd, keyVec[i]);
			else
				chan[chanVec[i]]->joinChannel(users, fd);
		}
		if (i < keyVec.size())
			keyVec.erase(keyVec.begin() + i);
	}
	
}

bool    Join::isNameValid(const std::string &name) const
{
    if (name == "0" || (!name.empty() && name.find_first_of("#") == 0))
        return true;
    return false;
}

Join	*Join::clone() const
{
	return (new Join);
}