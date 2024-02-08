/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:43:35 by mlagrini          #+#    #+#             */
/*   Updated: 2024/02/08 18:35:04 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCServer.hpp"

int	main(int ac, char **av)
{
	IRCServer	ParameterParser;
	if (ac != 3)
	{
		std::cout << "Wrong number of arguments!" << std::endl;
		return (1);
	}
	try
	{
		ParameterParser.checkParameters(av);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}