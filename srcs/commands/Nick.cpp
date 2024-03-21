#include "../includes/Nick.hpp"

Nick::Nick() : Command::Command()
{

}

Nick::~Nick()
{
	
}

int	Nick::doesUserExist(usrsMap &usrs, std::string nick) const
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

bool	Nick::doesChanExist(chanMap &chan, std::string name) const
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

void	Nick::execute(usrsMap &users, chanMap &chan, int fd) const
{
	(void) chan;
	if (users[fd]->isAuth())
	{
		send(fd, ERR_ALREADYREGISTERED(users[fd]->getNick()).c_str(), \
			ERR_ALREADYREGISTERED(users[fd]->getNick()).length(), 0);
		return;
	}
	if (users[fd]->getUserPass().empty())
		throw(Nick::registrationException());
	if (users[fd]->getCommand().size() < 2)
	{
		send(fd, ERR_NONICKNAMEGIVEN, sizeof(ERR_NONICKNAMEGIVEN), 0);
		throw(Nick::registrationException()); ;
	}
	else if (this->doesNameExist(users, users[fd]->getCommand()[FIRST_PARAM]))
	{
		send(fd, ERR_NICKNAMEINUSE(users[fd]->getCommand()[FIRST_PARAM]).c_str(), \
			ERR_NICKNAMEINUSE(users[fd]->getCommand()[FIRST_PARAM]).length(), 0);
		throw(Nick::registrationException()); ;
	}
	else if (this->containsRestrictedChar(users[fd]->getCommand()[FIRST_PARAM]) || \
		users[fd]->getCommand()[FIRST_PARAM].length() > 9)
	{
		send(fd, ERR_ERRONEUSNICKNAME(users[fd]->getCommand()[FIRST_PARAM]).c_str(), \
			ERR_ERRONEUSNICKNAME(users[fd]->getCommand()[FIRST_PARAM]).length(), 0);
		throw(Nick::registrationException()); ;
	}
	users[fd]->setNickname(users[fd]->getCommand()[FIRST_PARAM]);
}

Nick	*Nick::clone() const
{
	return (new Nick);
}

bool	Nick::doesNameExist(usrsMap users, std::string name) const
{
	usrsMap::iterator it = users.begin();
	while (it != users.end())
	{
		if (it->second->getNick() == name)
			return (true);
		it++;
	}
	return (false);
}

bool	Nick::containsRestrictedChar(std::string name) const
{
	if (name.empty() || name.find_first_of("#&:") == 0 \
		|| name.find_first_of(" ,*?@.") != std::string::npos)
		return (true);
	return (false);
}
