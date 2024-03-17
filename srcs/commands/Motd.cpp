#include "../includes/Motd.hpp"

Motd::Motd() : Command::Command()
{
	
}

Motd::~Motd()
{

}

void	Motd::execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const
{
	(void)chan;
	std::ifstream file("./srcs/motd.txt");
	std::string buffer;
	std::string line;
	if (!file.is_open())
	{
		send (fd, ERR_NOMOTD(users[fd]->getNickname()).c_str(), \
			ERR_NOMOTD(users[fd]->getNickname()).length(), 0);
		return ;
	}
	while (std::getline(file, line))
	{
		buffer += line + "\n";
	}
	file.close();
	buffer = RPL_MOTDSTART(users[fd]->getNickname()) + \
		RPL_MOTD(users[fd]->getNickname(), buffer) + RPL_ENDOFMOTD(users[fd]->getNickname());
	send (fd, buffer.c_str(), buffer.length(), 0);
}

Motd	*Motd::clone() const
{
	return (new Motd);
}