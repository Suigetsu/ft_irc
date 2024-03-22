#include "../includes/UserCmd.hpp"

UserCmd::UserCmd() : Command::Command()
{

}

UserCmd::~UserCmd()
{
	
}

int	UserCmd::doesUserExist(usrsMap &usrs, std::string nick) const
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

bool	UserCmd::doesChanExist(chanMap &chan, std::string name) const
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

strVector	UserCmd::parseParams(std::map<int, std::string> cmd, int fd, std::string nickname) const
{
	strVector params;
	std::stringstream ss(cmd[FIRST_PARAM]);
    std::string token;
	while (std::getline(ss, token, ' '))
	{
		if (token == ":")
		{
            std::getline(ss, token);
            params.push_back(token);
            break;
        }
        params.push_back(token);
	}
	if (params.size() != 4)
	{
		send(fd, ERR_NEEDMOREPARAMS(nickname, cmd[COMMAND]).c_str(), \
			ERR_NEEDMOREPARAMS(nickname, cmd[COMMAND]).length(), 0);
		throw (UserCmd::registrationException());
	}
	else if (this->containsRestrictedChar(params[0]) || params[0].length() > 9)
	{
		send(fd, ERR_ERRONEUSNICKNAME(params[0]).c_str(), \
			ERR_ERRONEUSNICKNAME(params[0]).length(), 0);
		throw (UserCmd::registrationException());
	}
	return (params);
}

void	UserCmd::execute(usrsMap &users, chanMap &chan, int fd) const
{
	(void) chan;
	strVector params;
	if (users[fd]->isAuth() == true)
	{
		send(fd, ERR_ALREADYREGISTERED(users[fd]->getNick()).c_str(), \
			ERR_ALREADYREGISTERED(users[fd]->getNick()).length(), 0);
		return ;
	}
	if (users[fd]->getUserPass().empty() || users[fd]->getNick().empty())
		throw(UserCmd::registrationException());
	if (users[fd]->getCommand().size() < 2)
	{
		send(fd, ERR_NEEDMOREPARAMS(users[fd]->getNick(), users[fd]->getCommand()[COMMAND]).c_str(), \
			ERR_NEEDMOREPARAMS(users[fd]->getNick(), users[fd]->getCommand()[COMMAND]).length(), 0);
		throw (UserCmd::registrationException());
	}
	params = this->parseParams(users[fd]->getCommand(), fd, users[fd]->getNick());
	users[fd]->setUsername(params[0]);
	users[fd]->setHost(params[2]);
	params[3].erase(0, params[3].find(":") + 1);
	users[fd]->setRealname(params[3]);
	users[fd]->setAuth(true);
	users[fd]->setFd(fd);
}

UserCmd	*UserCmd::clone() const
{
	return (new UserCmd);
}

bool	UserCmd::containsRestrictedChar(std::string name) const
{
	if (name.empty() || name.find_first_of("#&:") == 0 \
		|| name.find_first_of(" ,*?@.") != std::string::npos)
		return (true);
	return (false);
}