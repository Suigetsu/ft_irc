/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:16:57 by mlagrini          #+#    #+#             */
/*   Updated: 2024/02/10 17:05:04 by mlagrini         ###   ########.fr       */
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
	
	errno = 0;
	const long i = std::strtol(args[1], &pEnd, 10);
	if (errno == ERANGE || errno == EINVAL || *pEnd)
		throw (IRCServer::errorException());
	this->port = i;
	this->password = args[2];
}

long	IRCServer::getPort() const
{
	return (this->port);
}

std::string	IRCServer::getPassword() const
{
	return (this->password);
}
