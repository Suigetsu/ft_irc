#include "../includes/Ping.hpp"

Ping::Ping() : Command::Command()
{
	
}

Ping::~Ping()
{

}

void	Ping::execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const
{
	(void) chan;
	Pong obj;
	if (users[fd]->getCommand().size() < 2)
	{
		send (fd, ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).c_str(), \
			ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).length(), 0);
		throw (Ping::unknownCommandException());
	}
	obj.execute(users, chan, fd);
}

Ping	*Ping::clone() const
{
	return (new Ping);
}