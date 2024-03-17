#include "../includes/Pong.hpp"

Pong::Pong() : Command::Command()
{
	
}

Pong::~Pong()
{

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