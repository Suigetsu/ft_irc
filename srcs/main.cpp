/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:43:35 by mlagrini          #+#    #+#             */
/*   Updated: 2024/02/03 12:17:31 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

int	main(int ac, char **av)
{
	(void)av;
	if (ac != 3)
	{
		std::cout << "Wrong number of arguments!" << std::endl;
		return (1);
	}
	return (0);
}