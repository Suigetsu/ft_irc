/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:18:31 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/09 10:07:26 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Pass.hpp"
#include "../includes/Server.hpp"

Pass::Pass() : Command::Command()
{
	
}

Pass::~Pass()
{

}

void	Pass::execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const
{
	(void) chan;
	if (users[fd]->isAuth() == true)
	{
		send(fd, ERR_ALREADYREGISTERED(users[fd]->getNickname()).c_str(), \
			ERR_ALREADYREGISTERED(users[fd]->getNickname()).length(), 0);
		return ;
	}
	if (users[fd]->getCommand().size() < 2)
	{
		send(fd, ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).c_str(), \
			ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).length(), 0);
		throw (Pass::registrationException());
	}
	if (users[fd]->getCommand()[FIRST_PARAM] != users[fd]->getServerPass())
	{
		send(fd, ERR_PASSWDMISMATCH, sizeof(ERR_PASSWDMISMATCH), 0);
		throw (Pass::registrationException());
	}
	users[fd]->setUserPass(users[fd]->getCommand()[FIRST_PARAM]);
}

Pass	*Pass::clone() const
{
	return (new Pass);
}