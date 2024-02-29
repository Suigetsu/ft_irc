/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:18:31 by mlagrini          #+#    #+#             */
/*   Updated: 2024/02/28 16:40:21 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pass.hpp"

Pass::Pass() : Command::Command()
{
	
}

Pass::~Pass()
{

}

void	Pass::execute(std::map<int, User *> userMap, int clientFd) const
{
	if (userMap[clientFd]->getUserPass() != userMap[clientFd]->getServerPass())
	{
		send(clientFd, ERR_PASSWDMISMATCH, sizeof(ERR_PASSWDMISMATCH), 0);
		userMap[clientFd]->setAuth(false);
		return ;
	}
}

Pass	*Pass::clone() const
{
	return (new Pass);
}