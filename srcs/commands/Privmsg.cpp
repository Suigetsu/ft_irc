/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:52:40 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/09 10:07:26 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Privmsg.hpp"

Privmsg::Privmsg() : Command::Command()
{
	
}

Privmsg::~Privmsg()
{

}

void	Privmsg::execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const
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

Privmsg	*Privmsg::clone() const
{
	return (new Privmsg);
}