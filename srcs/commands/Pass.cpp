#include "../includes/Pass.hpp"
#include "../includes/Server.hpp"

Pass::Pass() : Command::Command()
{
	
}

Pass::~Pass()
{

}

int	Pass::doesUserExist(std::map<int, User *> &usrs, std::string nick) const
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

bool	Pass::doesChanExist(std::map<std::string, Channel *> &chan, std::string name) const
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

void	Pass::execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const
{
	(void) chan;
	if (users[fd]->isAuth() == true)
	{
		send(fd, ERR_ALREADYREGISTERED(users[fd]->getNickname()).c_str(), \
			ERR_ALREADYREGISTERED(users[fd]->getNickname()).length(), 0);
		return ;
	}
	if (users[fd]->getCommand().size() < 2)
	{
		send(fd, ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).c_str(), \
			ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).length(), 0);
		throw (Pass::registrationException());
	}
	if (users[fd]->getCommand()[FIRST_PARAM] != users[fd]->getServerPass())
	{
		send(fd, ERR_PASSWDMISMATCH, sizeof(ERR_PASSWDMISMATCH), 0);
		throw (Pass::registrationException());
	}
	users[fd]->setUserPass(users[fd]->getCommand()[FIRST_PARAM]);
}

Pass	*Pass::clone() const
{
	return (new Pass);
}