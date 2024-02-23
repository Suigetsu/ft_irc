/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:35:03 by mlagrini          #+#    #+#             */
/*   Updated: 2024/02/21 15:59:09 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client()
{
	
}

Client::~Client()
{
	
}

void	Client::setAddr(struct sockaddr_in addr)
{
	this->clientAddr = addr;
}

void	Client::setClientFd(int fd)
{
	this->clientFd = fd;
}

struct sockaddr_in	Client::getClientAddr()
{
	return (this->clientAddr);
}

int	Client::getClientFd()
{
	return (this->clientFd);
}
