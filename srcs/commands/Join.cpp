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
		keys = param.substr(0, param.find("\n"));
	}
	else
		chans = param.substr(0, param.find("\n"));
	chanVec = setChans(chans);
	keyVec = setKeys(keys);
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
		if (!chan[chanVec[i]])
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
    if (!name.empty() && name.find_first_of("#") == 0)
        return true;
    return false;
}

Join	*Join::clone() const
{
	return (new Join);
}