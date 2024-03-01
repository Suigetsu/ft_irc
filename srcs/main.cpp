/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:43:35 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/01 12:15:54 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

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
