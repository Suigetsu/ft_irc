/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:43:35 by mlagrini          #+#    #+#             */
/*   Updated: 2024/02/15 17:25:50 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCServer.hpp"

int	main(int ac, char **av)
{
	IRCServer	ParameterParser;
	if (ac != 3)
	{
		std::cout << "Wrong number of arguments!" << std::endl;
		std::cout << "Usage: " << av[0] << " <port> <password>" << std::endl;
		return (1);
	}
	try
	{
		ParameterParser.checkParameters(av);
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