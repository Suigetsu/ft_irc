#include <iostream>
#include <cstring>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BACKLOG 10

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "not enough arguments" << std::endl;
		return (1); 
	}
	struct addrinfo hints;
	struct addrinfo *address;
	int serverFd;
	int clientFd;
	int status;
	socklen_t addrSize;
	struct sockaddr_storage client_addr;

	std::memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	status = getaddrinfo(NULL, av[1], &hints, &address);
	if (status != 0)
	{
		std::cout << "An error occurred during the getaddrinfo phase" << std::endl;
		return (1);
	}
	serverFd = socket(address->ai_family, address->ai_socktype, address->ai_protocol);
	status = bind(serverFd, address->ai_addr, address->ai_addrlen);
	if (status != 0)
	{
		std::cout << "An error occurred during the bind phase" << std::endl;
		return (1);
	}
	listen(serverFd, BACKLOG);
	addrSize = sizeof(client_addr);
	clientFd = accept(serverFd, (struct sockaddr *)&client_addr, &addrSize);
	if (clientFd == -1)
	{
		std::cout << "An error occurred during the accept phase" << std::endl;
		return (1);
	}
	std::cout << "Server FD: " << serverFd << "\nClient FD: " << clientFd << std::endl;
	close (serverFd);
	close (clientFd);
	return (0);
}