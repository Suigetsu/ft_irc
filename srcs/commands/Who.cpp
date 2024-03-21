#include "../includes/Who.hpp"

Who::Who() : Command::Command()
{
	
}

Who::~Who()
{

}

int	Who::doesUserExist(usrsMap &usrs, std::string nick) const
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

bool	Who::doesChanExist(chanMap &chan, std::string name) const
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

void	Who::sendWho(User *usr, Channel *chan, int fd) const
{
	std::vector<User *> tmp = chan->getUsers();
	std::string buffer;
	std::vector<User *>::iterator it = tmp.begin();
	while (it != tmp.end())
	{
		buffer += RPL_WHOREPLY(usr->getNick(), chan->getName(), (*it)->getName(), \
			(*it)->getHost(), (*it)->getNick(), (*it)->getRealname());
		it++;
	}
	buffer += RPL_ENDOFWHO(usr->getNick(), chan->getName());
	send (fd, buffer.c_str(), buffer.length(), 0);
}

void	Who::execute(usrsMap &users, chanMap &chan, int fd) const
{
	if (users[fd]->getCommand().size() < 2)
	{
		send (fd, ERR_NEEDMOREPARAMS(users[fd]->getNick(), users[fd]->getCommand()[COMMAND]).c_str(), \
			ERR_NEEDMOREPARAMS(users[fd]->getNick(), users[fd]->getCommand()[COMMAND]).length(), 0);
		throw (Who::unknownCommandException());
	}
	if (!this->doesChanExist(chan, users[fd]->getCommand()[FIRST_PARAM]))
	{
		send (fd, RPL_ENDOFWHO(users[fd]->getNick(), users[fd]->getCommand()[FIRST_PARAM]).c_str(), \
			RPL_ENDOFWHO(users[fd]->getNick(), users[fd]->getCommand()[FIRST_PARAM]).length(), 0);
		return ;
	}
	this->sendWho(users[fd], chan[users[fd]->getCommand()[FIRST_PARAM]], fd);
}

Who	*Who::clone() const
{
	return (new Who);
}