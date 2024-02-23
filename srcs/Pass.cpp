/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:18:31 by mlagrini          #+#    #+#             */
/*   Updated: 2024/02/23 10:04:42 by mlagrini         ###   ########.fr       */
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
	if (userMap[clientFd]->isAuth() == true)
		return ;
	if (userMap[clientFd]->getUserPass() != userMap[clientFd]->getServerPass())
	{
		send(clientFd, "Wrong password\r\n", 17, 0);
		return ;
	}
	send(clientFd, "Connection went through\r\n", 26, 0);
}

Pass	*Pass::clone() const
{
	return (new Pass);
}