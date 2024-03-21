#include "../includes/Ping.hpp"

Ping::Ping() : Command::Command()
{
	
}

Ping::~Ping()
{

}

int	Ping::doesUserExist(usrsMap &usrs, std::string nick) const
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

bool	Ping::doesChanExist(chanMap &chan, std::string name) const
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

void	Ping::execute(usrsMap &users, chanMap &chan, int fd) const
{
	(void) chan;
	Pong obj;
	if (users[fd]->getCommand().size() < 2)
	{
		send (fd, ERR_NEEDMOREPARAMS(users[fd]->getNick(), users[fd]->getCommand()[COMMAND]).c_str(), \
			ERR_NEEDMOREPARAMS(users[fd]->getNick(), users[fd]->getCommand()[COMMAND]).length(), 0);
		return ;
	}
	obj.execute(users, chan, fd);
}

Ping	*Ping::clone() const
{
	return (new Ping);
}