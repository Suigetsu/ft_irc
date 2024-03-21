#include "../includes/Pong.hpp"

Pong::Pong() : Command::Command()
{
	
}

Pong::~Pong()
{

}

int	Pong::doesUserExist(usrsMap &usrs, std::string nick) const
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

bool	Pong::doesChanExist(chanMap &chan, std::string name) const
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

void	Pong::execute(usrsMap &users, chanMap &chan, int fd) const
{
    (void) chan;
    send(fd, PONG(users[fd]->getCommand()[FIRST_PARAM]).c_str(), \
        PONG(users[fd]->getCommand()[FIRST_PARAM]).length(), 0);
}

Pong	*Pong::clone() const
{
	return (new Pong);
}