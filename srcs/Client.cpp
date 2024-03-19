#include "./includes/Client.hpp"

Client::Client()
{
	
}

Client::~Client()
{
	
}

void	Client::setAddr(struct sockaddr_in addr)
{
	this->clientAddr = addr;
}

void	Client::setClientFd(int fd)
{
	this->clientFd = fd;
}

struct sockaddr_in	Client::getClientAddr()
{
	return (this->clientAddr);
}

int	Client::getClientFd()
{
	return (this->clientFd);
}
