/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:14:43 by hrahmane          #+#    #+#             */
/*   Updated: 2024/03/09 10:07:26 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Ping.hpp"

Ping::Ping() : Command::Command()
{
	
}

Ping::~Ping()
{

}

void	Ping::execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const
{
	(void)chan, (void)users, (void)fd;
}

Ping	*Ping::clone() const
{
	return (new Ping);
}