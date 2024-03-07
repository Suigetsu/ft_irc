/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:14:43 by hrahmane          #+#    #+#             */
/*   Updated: 2024/03/07 11:49:18 by hrahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Ping.hpp"

Ping::Ping() : Command::Command()
{
	
}

Ping::~Ping()
{

}

void	Ping::execute(std::map<int, User *> users, std::map<std::string, Channel *> chan, int fd) const
{
	(void)chan, (void)users, (void)fd;
}

Ping	*Ping::clone() const
{
	return (new Ping);
}