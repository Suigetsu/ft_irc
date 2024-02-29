/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:47:46 by mlagrini          #+#    #+#             */
/*   Updated: 2024/02/29 14:29:48 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nick.hpp"

Nick::Nick() : Command::Command()
{
	
}

Nick::~Nick()
{

}

void	Nick::execute(std::map<int, User *> userMap, int clientFd) const
{
	if (this->doesNameExist(userMap, userMap[clientFd]->getNickname()) == true)
	{
		
	}
}

Nick	*Nick::clone() const
{
	return (new Nick);
}

bool	Nick::doesNameExist(std::map<int, User *> userMap, std::string name) const
{
	std::map<int, User *>::iterator it = userMap.begin();
	while (it != userMap.end())
	{
		if (it->second->getNickname() == name)
			return (true);
		it++;
	}
	return (false);
}
