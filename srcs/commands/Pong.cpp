#include "../includes/Pong.hpp"

Pong::Pong() : Command::Command()
{
	
}

Pong::~Pong()
{

}

int	Pong::doesUserExist(std::map<int, User *> &usrs, std::string nick) const
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

bool	Pong::doesChanExist(std::map<std::string, Channel *> &chan, std::string name) const
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

void	Pong::execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const
{
    (void) chan;
    send(fd, PONG(users[fd]->getCommand()[FIRST_PARAM]).c_str(), \
        PONG(users[fd]->getCommand()[FIRST_PARAM]).length(), 0);
}

Pong	*Pong::clone() const
{
	return (new Pong);
}