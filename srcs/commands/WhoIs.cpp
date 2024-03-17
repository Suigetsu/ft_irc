#include "../includes/WhoIs.hpp"

WhoIs::WhoIs() : Command::Command()
{
	
}

WhoIs::~WhoIs()
{

}

std::string	WhoIs::getWhoIsChannelsBuffer(std::map<std::string, Channel *> &chan, std::string nick) const
{
	std::string buffer;
	std::map<std::string, Channel *>::iterator it = chan.begin();
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

void	WhoIs::sendWhoIs(User *client, User *whoUsr, std::map<std::string, Channel *> &chan, int fd) const
{
	std::string chanBuff;
	if (!this->getWhoIsChannelsBuffer(chan, whoUsr->getNickname()).empty())
		chanBuff = RPL_WHOISCHANNELS(client->getNickname(), whoUsr->getNickname(), \
		this->getWhoIsChannelsBuffer(chan, whoUsr->getNickname()));
	std::string buffer = RPL_WHOISUSER(client->getNickname(), whoUsr->getNickname(), \
		whoUsr->getUsername(), whoUsr->getHost(), whoUsr->getRealname()) \
		+ chanBuff + RPL_WHOISSERVER(client->getNickname(), whoUsr->getNickname()) \
		+ RPL_ENDOFWHOIS(client->getNickname(), whoUsr->getNickname());
	send (fd, buffer.c_str(), buffer.length(), 0);
}

User	*WhoIs::getUser(std::map<int, User *> &users, const std::string &name) const
{
	std::map<int, User *>::iterator it = users.begin();
	while (it != users.end())
	{
		if ((*it).second->getNickname() == name)
			return it->second;
		it++;
	}
	return NULL;
}

void	WhoIs::execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const
{
	if (users[fd]->getCommand().size() < 2)
	{
		send (fd, ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).c_str(), \
			ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).length(), 0);
		throw (WhoIs::unknownCommandException());
	}
	if (this->getUser(users, users[fd]->getCommand()[FIRST_PARAM]) == NULL)
	{
		std::string buffer = ERR_NOSUCHNICK(users[fd]->getNickname(), users[fd]->getCommand()[FIRST_PARAM]) \
			+ RPL_ENDOFWHOIS(users[fd]->getNickname(), users[fd]->getCommand()[FIRST_PARAM]);
		send (fd, buffer.c_str(), buffer.length(), 0);
		return ;
	}
	this->sendWhoIs(users[fd], this->getUser(users, users[fd]->getCommand()[FIRST_PARAM]), chan, fd);
}

WhoIs	*WhoIs::clone() const
{
	return (new WhoIs);
}