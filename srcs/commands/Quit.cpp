/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:48:03 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/04 18:24:41 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Quit.hpp"

Quit::Quit() : Command::Command()
{
	
}

Quit::~Quit()
{

}

void	Quit::execute(std::map<int, User *> userMap, std::map<std::string, Channel *> chan, int clientFd) const
{
	(void)chan;
	std::string reason;
	if (userMap[clientFd]->getCommand().size() == 1)
		reason = "Leaving";
	else
		reason = userMap[clientFd]->getCommand()[FIRST_PARAM];
	send(clientFd, QUIT_MSG(userMap[clientFd]->getNickname(),userMap[clientFd]->getUsername(),userMap[clientFd]->getHost(), reason).c_str(), \
		QUIT_MSG(userMap[clientFd]->getNickname(),userMap[clientFd]->getUsername(),userMap[clientFd]->getHost(), reason).length(), 0);
}

Quit	*Quit::clone() const
{
	return (new Quit);
}