#include "../includes/Who.hpp"

Who::Who() : Command::Command()
{
	
}

Who::~Who()
{

}

void	Who::sendWho(User *usr, Channel *chan, int fd) const
{
	std::vector<User *> tmp = chan->getUsers();
	std::string buffer;
	std::vector<User *>::iterator it = tmp.begin();
	while (it != tmp.end())
	{
		buffer += RPL_WHOREPLY(usr->getNickname(), chan->getName(), (*it)->getUsername(), \
			(*it)->getHost(), (*it)->getNickname(), (*it)->getRealname());
		it++;
	}
	buffer += RPL_ENDOFWHO(usr->getNickname(), chan->getName());
	send (fd, buffer.c_str(), buffer.length(), 0);
}

void	Who::execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const
{
	if (users[fd]->getCommand().size() < 2)
	{
		send (fd, ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).c_str(), \
			ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).length(), 0);
		throw (Who::unknownCommandException());
	}
	if (!chan[users[fd]->getCommand()[FIRST_PARAM]])
	{
		send (fd, RPL_ENDOFWHO(users[fd]->getNickname(), users[fd]->getCommand()[FIRST_PARAM]).c_str(), \
			RPL_ENDOFWHO(users[fd]->getNickname(), users[fd]->getCommand()[FIRST_PARAM]).length(), 0);
		return ;
	}
	this->sendWho(users[fd], chan[users[fd]->getCommand()[FIRST_PARAM]], fd);
}

Who	*Who::clone() const
{
	return (new Who);
}