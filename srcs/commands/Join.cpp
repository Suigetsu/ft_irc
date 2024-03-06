/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:01:56 by hrahmane          #+#    #+#             */
/*   Updated: 2024/03/04 18:38:33 by hrahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Join.hpp"

Join::Join() : Command::Command()
{
	
}

Join::~Join()
{

}

void	Join::execute(std::map<int, User *> userMap, std::map<std::string, Channel *> chan, int clientFd) const
{
	//check
	// userMap[clientFd]->getCommand()[FIRST_PARAM].length()
	// chan.find(userMap[clientFd]->getCommand()[COMMAND]);
	if (!this->isNameValid(userMap[clientFd]->getCommand()[FIRST_PARAM]))
		throw(Command::unknownCommandException());
	
	
}

bool    Join::isNameValid(const std::string &name) const
{
    if (name.empty() && name.find_first_of("&#+!") == 0)
        return true;
    return false;
}

Join	*Join::clone() const
{
	return (new Join);
}