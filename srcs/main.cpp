#include "./includes/Server.hpp"

int	main(int ac, char **av)
{
	Server	servObject;
	if (ac != 3)
	{
		std::cout << "Wrong number of arguments!" << std::endl;
		std::cout << "Usage: " << av[0] << " <port> <password>" << std::endl;
		return (1);
	}
	try
	{
		servObject.checkParameters(av);
		std::signal(SIGINT, Server::signalHandler);
		std::signal(SIGQUIT, Server::signalHandler);
		servObject.initServer();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}

