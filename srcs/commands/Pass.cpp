/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:18:31 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/06 17:17:47 by hrahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Pass.hpp"

Pass::Pass() : Command::Command()
{
	
}

Pass::~Pass()
{

}

void	Pass::execute(std::map<int, User *> users, std::map<std::string, Channel *> chan, int fd) const
{
	(void) chan;
	if (users[fd]->isAuth() == true)
	{
		send(fd, ERR_ALREADYREGISTERED, sizeof(ERR_ALREADYREGISTERED), 0);
		return ;
	}
	if (users[fd]->getCommand().size() < 2)
	{
		send(fd, ERR_NEEDMOREPARAMS(users[fd]->getCommand()[COMMAND]).c_str(), \
			ERR_NEEDMOREPARAMS(users[fd]->getCommand()[COMMAND]).length(), 0);
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