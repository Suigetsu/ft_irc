/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:01:56 by hrahmane          #+#    #+#             */
/*   Updated: 2024/03/07 17:05:54 by hrahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Join.hpp"

Join::Join() : Command::Command()
{
	
}

Join::~Join()
{

}

void	Join::setChans(const std::string &list)
{
	std::istringstream iss(list);
	std::string token;
	while (std::getline(iss, token, ','))
	{
		this->chans.push_back(token);
	}
}

void	Join::setKeys(const std::string &list)
{
	std::istringstream iss(list);
	std::string token;
	while (std::getline(iss, token, ','))
	{
		this->chans.push_back(token);
	}
}

const std::vector<std::string> &Join::getChans() const
{
	return (this->chans);
}

const std::vector<std::string> &Join::getKeys() const
{
	return (this->keys);
}

void	Join::parseChannels(std::string param)
{
	std::string chans;
	std::string keys;
	if (param.find(" ") != std::string::npos)
	{
		chans = param.substr(0, param.find(" "));
		param.erase(0, param.find(" ") + 1);
		keys = param.substr(0, param.find("\n"));
	}
	else
		chans = param.substr(0, param.find("\n"));
	this->setChans(chans);
	this->setKeys(keys);
}

void	Join::execute(std::map<int, User *> users, std::map<std::string, Channel *> chan, int fd) const
{
	(void)chan;
	//check
	// users[fd]->getCommand()[FIRST_PARAM].length()
	// chan.find(users[fd]->getCommand()[COMMAND]);
	if (users[fd]->getCommand().size() < 2)
	{
		send (fd, ERR_NEEDMOREPARAMS(users[fd]->getCommand()[COMMAND]).c_str(), \
		ERR_NEEDMOREPARAMS(users[fd]->getCommand()[COMMAND]).length(), 0);
		throw (Join::unknownCommandException());
	}
	
	// if (!this->isNameValid(users[fd]->getCommand()[FIRST_PARAM]))
	// 	throw(Command::unknownCommandException());
	
	
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