/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:19:59 by hrahmane          #+#    #+#             */
/*   Updated: 2024/03/07 11:33:00 by hrahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Pong.hpp"

Pong::Pong() : Command::Command()
{
	
}

Pong::~Pong()
{

}

void	Pong::execute(std::map<int, User *> users, std::map<std::string, Channel *> chan, int fd) const
{
	(void)chan;
    std::string buffer = "PONG ircserv " + users[fd]->getCommand()[FIRST_PARAM];
    send(fd, buffer.c_str(), buffer.length(), 0);
}

Pong	*Pong::clone() const
{
	return (new Pong);
}