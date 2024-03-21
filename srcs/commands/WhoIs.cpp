#include "../includes/WhoIs.hpp"

WhoIs::WhoIs() : Command::Command()
{
	
}

WhoIs::~WhoIs()
{

}

int	WhoIs::doesUserExist(usrsMap &usrs, std::string nick) const
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

bool	WhoIs::doesChanExist(chanMap &chan, std::string name) const
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

std::string	WhoIs::getWhoIsChannelsBuffer(chanMap &chan, std::string nick) const
{
	std::string buffer;
	chanMap::iterator it = chan.begin();
	while (it != chan.end())
	{
		if (it->second->isWithinChannel(nick) == true)
		{
			if (it->second->isOperator(nick))
				buffer += "@";
			buffer += it->second->getName();
			buffer += " ";
		}
		it++;
	}
	return (buffer);
}

void	WhoIs::sendWhoIs(User *client, User *whoUsr, chanMap &chan, int fd) const
{
	std::string chanBuff;
	if (!this->getWhoIsChannelsBuffer(chan, whoUsr->getNick()).empty())
		chanBuff = RPL_WHOISCHANNELS(client->getNick(), whoUsr->getNick(), \
		this->getWhoIsChannelsBuffer(chan, whoUsr->getNick()));
	std::string buffer = RPL_WHOISUSER(client->getNick(), whoUsr->getNick(), \
		whoUsr->getName(), whoUsr->getHost(), whoUsr->getRealname()) \
		+ chanBuff + RPL_WHOISSERVER(client->getNick(), whoUsr->getNick()) \
		+ RPL_ENDOFWHOIS(client->getNick(), whoUsr->getNick());
	send (fd, buffer.c_str(), buffer.length(), 0);
}

User	*WhoIs::getUser(usrsMap &users, const std::string &name) const
{
	usrsMap::iterator it = users.begin();
	while (it != users.end())
	{
		if ((*it).second->getNick() == name)
			return it->second;
		it++;
	}
	return NULL;
}

void	WhoIs::execute(usrsMap &users, chanMap &chan, int fd) const
{
	if (users[fd]->getCommand().size() < 2)
	{
		send (fd, ERR_NEEDMOREPARAMS(users[fd]->getNick(), users[fd]->getCommand()[COMMAND]).c_str(), \
			ERR_NEEDMOREPARAMS(users[fd]->getNick(), users[fd]->getCommand()[COMMAND]).length(), 0);
		throw (WhoIs::unknownCommandException());
	}
	if (this->getUser(users, users[fd]->getCommand()[FIRST_PARAM]) == NULL)
	{
		std::string buffer = ERR_NOSUCHNICK(users[fd]->getNick(), users[fd]->getCommand()[FIRST_PARAM]) \
			+ RPL_ENDOFWHOIS(users[fd]->getNick(), users[fd]->getCommand()[FIRST_PARAM]);
		send (fd, buffer.c_str(), buffer.length(), 0);
		return ;
	}
	this->sendWhoIs(users[fd], this->getUser(users, users[fd]->getCommand()[FIRST_PARAM]), chan, fd);
}

WhoIs	*WhoIs::clone() const
{
	return (new WhoIs);
}