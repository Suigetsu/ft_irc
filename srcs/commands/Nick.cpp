/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:47:46 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/04 16:36:04 by hrahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Nick.hpp"

Nick::Nick() : Command::Command()
{

}

Nick::~Nick()
{
	
}

void	Nick::execute(std::map<int, User *> userMap, std::map<std::string, Channel *> chan, int clientFd) const
{
	(void) chan;
	if (this->doesNameExist(userMap, userMap[clientFd]->getNickHelper()))
	{
		send(clientFd, ERR_NICKNAMEINUSE(userMap[clientFd]->getNickHelper()).c_str(), \
			ERR_NICKNAMEINUSE(userMap[clientFd]->getNickHelper()).length(), 0);
		throw (Nick::registrationException());
	}
	else if (userMap[clientFd]->getNickHelper().empty())
	{
		send(clientFd, ERR_NONICKNAMEGIVEN, sizeof(ERR_NONICKNAMEGIVEN), 0);
		throw (Nick::registrationException());
	}
	else if (this->containsRestrictedChar(userMap[clientFd]->getNickHelper()))
	{
		send(clientFd, ERR_ERRONEUSNICKNAME(userMap[clientFd]->getNickHelper()).c_str(), \
			ERR_ERRONEUSNICKNAME(userMap[clientFd]->getNickHelper()).length(), 0);
		throw (Nick::registrationException());
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

bool	Nick::containsRestrictedChar(std::string name) const
{
	if (name.empty() || name.find_first_of("#&:") == 0 \
		|| name.find_first_of(" ,*?@.") != std::string::npos)
		return (true);
	return (false);
}
