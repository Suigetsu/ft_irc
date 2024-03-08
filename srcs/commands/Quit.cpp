/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:48:03 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/07 12:48:48 by hrahmane         ###   ########.fr       */
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
	userMap.erase(clientFd);
}

Quit	*Quit::clone() const
{
	return (new Quit);
}