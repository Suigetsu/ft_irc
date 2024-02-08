/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:16:57 by mlagrini          #+#    #+#             */
/*   Updated: 2024/02/08 18:34:50 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCServer.hpp"

IRCServer::IRCServer()
{
	
}

IRCServer::~IRCServer()
{

}

const char	*IRCServer::errorException::what() const throw()
{
	return ("The parameters you entered are wrong.");
}

void	IRCServer::checkParameters(char **args)
{
	char *pEnd = NULL;
	int ac = 1;
	
	errno = 0;
	while (ac < 3)
	{
		const long i = std::strtol(args[ac], &pEnd, 10);
		if (errno == ERANGE || errno == EINVAL || *pEnd)
			throw (IRCServer::errorException());
		this->PortPasswordMap[ac - 1] = i;
		ac++;
	}
}
