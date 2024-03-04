/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:48:03 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/04 15:48:22 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Quit.hpp"

Quit::Quit() : Command::Command()
{
	
}

Quit::~Quit()
{

}

void	Quit::execute(std::map<int, User *> userMap, int clientFd) const
{
	if (userMap[clientFd]->getCommand().size() < 3)
	{
		if (userMap[clientFd]->getCommand().size() == 2)
		{
			send(clientFd, ERR_NOTEXTTOSEND, sizeof(ERR_NOTEXTTOSEND), 0);
			return ;
		}
		send(clientFd, ERR_NORECIPIENT(userMap[clientFd]->getCommand()[COMMAND]).c_str(), \
			ERR_NORECIPIENT(userMap[clientFd]->getCommand()[COMMAND]).length(), 0);
		return ;
	}
	
}

Quit	*Quit::clone() const
{
	return (new Quit);
}