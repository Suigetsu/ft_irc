/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:00:01 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/05 14:41:03 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/User.hpp"

User::User() {}

User::User(std::string pass)
{
	this->auth = false;
	this->serverPass = pass;
}

User::~User()
{
	
}

User	*User::clone(std::string pass) const
{
	return (new User(pass));
}

void	User::setNickname(std::string name)
{
	this->nickname = name;
}

void	User::setUsername(std::string name)
{
	this->username = name;
}

void	User::setUserPass(std::string pass)
{
	this->userPass = pass;
}

void	User::setAuth(bool auth)
{
	this->auth = auth;
}

void	User::setHost(std::string host)
{
	this->host = host;
}

void	User::setRealname(std::string name)
{
	this->realname = name;
}

void	User::setNickHelper(std::string name)
{
	this->nicknameHelper = name;
}

std::string	User::getNickname()
{
	return (this->nickname);
}

std::string	User::getUsername()
{
	return (this->username);
}

std::string	User::getUserPass()
{
	return (this->userPass);
}

std::string	User::getServerPass()
{
	return (this->serverPass);
}

bool	User::isAuth()
{
	return (this->auth);
}

std::string	User::getHost()
{
	return (this->host);
}

std::string	User::getRealname()
{
	return (this->realname);
}

std::string	User::getNickHelper()
{
	return (this->nicknameHelper);
}

void	User::parseCommand(std::string command)
{
	if (command.find(" ") != std::string::npos)
	{
		cmd[COMMAND] = command.substr(0, command.find(" "));
		command.erase(0, command.find(" ") + 1);
		cmd[FIRST_PARAM] = command.substr(0, command.find("\r"));
		return ;
	}
	cmd[COMMAND] = command.substr(0, command.find("\n"));
	// std::istringstream iss(command);
	// std::string token;
	// while (std::getline(iss, token, ' ') && i < 2)
	// {
	// 	this->cmd[i] = token;
	// 	i++;
	// }
}

std::map<int, std::string>	&User::getCommand()
{
	return (this->cmd);
}
