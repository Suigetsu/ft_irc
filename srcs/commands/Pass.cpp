/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:18:31 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/04 16:35:54 by hrahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Pass.hpp"

Pass::Pass() : Command::Command()
{
	
}

Pass::~Pass()
{

}

void	Pass::execute(std::map<int, User *> userMap, std::map<std::string, Channel *> chan, int clientFd) const
{
	(void) chan;
	if (userMap[clientFd]->getUserPass() != userMap[clientFd]->getServerPass())
	{
		send(clientFd, ERR_PASSWDMISMATCH, sizeof(ERR_PASSWDMISMATCH), 0);
		userMap[clientFd]->setAuth(false);
		throw (Pass::registrationException());
	}
}

Pass	*Pass::clone() const
{
	return (new Pass);
}