#include "./includes/Server.hpp"

int	maine(int ac, char **av)
{
	Server	ParameterParser;
	if (ac != 3)
	{
		std::cout << "Wrong number of arguments!" << std::endl;
		std::cout << "Usage: " << av[0] << " <port> <password>" << std::endl;
		return (1);
	}
	try
	{
		ParameterParser.checkParameters(av);
		std::signal(SIGINT, Server::signalHandler);
		std::signal(SIGQUIT, Server::signalHandler);
		ParameterParser.initServer();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	// ParameterParser.init(ParameterParser.getPort());
	return (0);
}

int	main(int ac, char **av)
{
	int i = maine(ac, av);
	system("leaks -q ircserv");
	return (i);
}
