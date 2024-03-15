/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:19:59 by hrahmane          #+#    #+#             */
/*   Updated: 2024/03/15 12:36:29 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Pong.hpp"

Pong::Pong() : Command::Command()
{
	
}

Pong::~Pong()
{

}

void	Pong::execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const
{
    (void) chan;
    send(fd, PONG(users[fd]->getCommand()[FIRST_PARAM]).c_str(), \
        PONG(users[fd]->getCommand()[FIRST_PARAM]).length(), 0);
}

Pong	*Pong::clone() const
{
	return (new Pong);
}