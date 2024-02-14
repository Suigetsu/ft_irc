#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <netdb.h>

int	main(int ac, char **av)
{
	struct addrinfo hint;
	struct addrinfo *result;
	struct addrinfo *iterPtr;
	int status;
	char buffer[INET6_ADDRSTRLEN];

	if (ac != 2)
	{
		std::cout << "Error" << std::endl;
		return (1);
	}
	std::memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_STREAM;
	if ((status = getaddrinfo(av[1], NULL, &hint, &result)) != 0)
	{
		std::cout << "Error in the getaddrinfo function" << std::endl;
		return (1);
	}
	iterPtr = result;
	std::cout << "Adresses for " << av[1] << ":" << std::endl;
	while (iterPtr != NULL)
	{
		void *addr;
		if (iterPtr->ai_family == AF_INET)
		{
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)iterPtr->ai_addr;
			inet_ntop(iterPtr->ai_family, &(ipv4->sin_addr), buffer, sizeof(buffer));
			std::cout << "IPv4: " << buffer << std::endl;
		}
		else
		{
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)iterPtr->ai_addr;
			inet_ntop(iterPtr->ai_family, &(ipv6->sin6_addr), buffer, sizeof(buffer));
			std::cout << "IPv6: " << buffer << std::endl;
		}
	}
	freeaddrinfo(result);
}