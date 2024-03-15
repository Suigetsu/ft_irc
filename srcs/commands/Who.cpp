/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:05:55 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/15 13:16:51 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Who.hpp"

Who::Who() : Command::Command()
{
	
}

Who::~Who()
{

}

void	Who::sendWho(User *usr, Channel *chan, int fd) const
{
	std::vector<User *> tmp = chan->getUsers();
	std::vector<User *>::iterator it = tmp.begin();
	while (it != tmp.end())
	{
		send (fd, RPL_WHOREPLY(usr->getNickname(), chan->getName(), (*it)->getUsername(), \
			(*it)->getHost(), (*it)->getNickname(), (*it)->getRealname()).c_str(), \
			RPL_WHOREPLY(usr->getNickname(), chan->getName(), (*it)->getUsername(), \
			(*it)->getHost(), (*it)->getNickname(), (*it)->getRealname()).length(), 0);
		it++;
	}
	send (fd, RPL_ENDOFWHO(usr->getNickname(), chan->getName()).c_str(), \
			RPL_ENDOFWHO(usr->getNickname(), chan->getName()).length(), 0);
}

void	Who::execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const
{
	if (users[fd]->getCommand().size() < 2)
	{
		send (fd, ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).c_str(), \
			ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).length(), 0);
		throw (Who::unknownCommandException());
	}
	if (!chan[users[fd]->getCommand()[FIRST_PARAM]])
	{
		send (fd, RPL_ENDOFWHO(users[fd]->getNickname(), users[fd]->getCommand()[FIRST_PARAM]).c_str(), \
			RPL_ENDOFWHO(users[fd]->getNickname(), users[fd]->getCommand()[FIRST_PARAM]).length(), 0);
		return ;
	}
	this->sendWho(users[fd], chan[users[fd]->getCommand()[FIRST_PARAM]], fd);
}

Who	*Who::clone() const
{
	return (new Who);
}