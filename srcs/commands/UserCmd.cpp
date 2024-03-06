/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:30:19 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/06 16:07:09 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/UserCmd.hpp"

UserCmd::UserCmd() : Command::Command()
{

}

UserCmd::~UserCmd()
{
	
}

std::vector<std::string>	UserCmd::parseParams(std::map<int, std::string> cmd, int fd) const
{
	std::vector<std::string> params;
	std::stringstream ss(cmd[FIRST_PARAM]);
    std::string token;
	while (std::getline(ss, token, ' '))
	{
		if (token == ":")
		{
            std::getline(ss, token);
            params.push_back(token);
            break;
        }
        params.push_back(token);
	}
	if (params.size() < 4)
	{
		send(fd, ERR_NEEDMOREPARAMS(cmd[COMMAND]).c_str(), \
			ERR_NEEDMOREPARAMS(cmd[COMMAND]).length(), 0);
		throw (UserCmd::registrationException());
	}
	else if (this->containsRestrictedChar(params[0]) || params[0].length() > 9)
	{
		send(fd, ERR_ERRONEUSNICKNAME(params[0]).c_str(), \
			ERR_ERRONEUSNICKNAME(params[0]).length(), 0);
		throw (UserCmd::registrationException());
	}
	return (params);
}

void	UserCmd::execute(std::map<int, User *> users, std::map<std::string, Channel *> chan, int fd) const
{
	(void) chan;
	if (users[fd]->isAuth() == true)
	{
		send(fd, ERR_ALREADYREGISTERED, sizeof(ERR_ALREADYREGISTERED), 0);
		return ;
	}
	std::vector<std::string> params;
	if (users[fd]->getCommand().size() < 2)
	{
		send(fd, ERR_NEEDMOREPARAMS(users[fd]->getCommand()[COMMAND]).c_str(), \
			ERR_NEEDMOREPARAMS(users[fd]->getCommand()[COMMAND]).length(), 0);
		throw (UserCmd::registrationException());
	}
	params = this->parseParams(users[fd]->getCommand(), fd);
	users[fd]->setUsername(params[0]);
	users[fd]->setHost(params[2]);
	users[fd]->setRealname(params[3]);
	users[fd]->setAuth(true);
}

UserCmd	*UserCmd::clone() const
{
	return (new UserCmd);
}

bool	UserCmd::doesNameExist(std::map<int, User *> users, std::string name) const
{
	std::map<int, User *>::iterator it = users.begin();
	while (it != users.end())
	{
		if (it->second->getNickname() == name)
			return (true);
		it++;
	}
	return (false);
}

bool	UserCmd::containsRestrictedChar(std::string name) const
{
	if (name.empty() || name.find_first_of("#&:") == 0 \
		|| name.find_first_of(" ,*?@.") != std::string::npos)
		return (true);
	return (false);
}