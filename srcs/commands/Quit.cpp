#include "../includes/Quit.hpp"

Quit::Quit() : Command::Command()
{
	
}

Quit::~Quit()
{

}

void	Quit::execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const
{
	(void)chan;
	std::string reason;
	if (users[fd]->getCommand().size() == 1)
		reason = "Leaving";
	else
		reason = users[fd]->getCommand()[FIRST_PARAM];
	send(fd, QUIT_MSG(users[fd]->getNickname(),users[fd]->getUsername(),users[fd]->getHost(), reason).c_str(), \
		QUIT_MSG(users[fd]->getNickname(),users[fd]->getUsername(),users[fd]->getHost(), reason).length(), 0);
	Server::QuitStatus = true;
	// delete users[fd];
	// users.erase(fd);
	// close (fd);
}

Quit	*Quit::clone() const
{
	return (new Quit);
}