#include "../includes/Motd.hpp"

Motd::Motd() : Command::Command()
{
	
}

Motd::~Motd()
{

}

int	Motd::doesUserExist(usrsMap &usrs, std::string nick) const
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

bool	Motd::doesChanExist(chanMap &chan, std::string name) const
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

void	Motd::execute(usrsMap &users, chanMap &chan, int fd) const
{
	(void)chan;
	std::ifstream file("./srcs/motd.txt");
	std::string buffer;
	std::string line;
	if (!file.is_open())
	{
		send (fd, ERR_NOMOTD(users[fd]->getNick()).c_str(), \
			ERR_NOMOTD(users[fd]->getNick()).length(), 0);
		return ;
	}
	while (std::getline(file, line))
	{
		buffer += line + "\n";
	}
	file.close();
	buffer = RPL_MOTDSTART(users[fd]->getNick()) + \
		RPL_MOTD(users[fd]->getNick(), buffer) + RPL_ENDOFMOTD(users[fd]->getNick());
	send (fd, buffer.c_str(), buffer.length(), 0);
}

Motd	*Motd::clone() const
{
	return (new Motd);
}