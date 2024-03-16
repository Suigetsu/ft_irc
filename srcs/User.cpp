/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:00:01 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/16 12:57:47 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/User.hpp"

User::User() {}

User::User(std::string pass)
{
	this->auth = false;
	this->serverPass = pass;
	this->prefix = "";
}

User::~User()
{
	
}

User	*User::clone(std::string pass) const
{
	return (new User(pass));
}

void	User::setFd(int fd)
{
	this->fd = fd;
}

void	User::setNickname(const std::string &name)
{
	this->nickname = name;
}

void	User::setUsername(const std::string &name)
{
	this->username = name;
}

void	User::setUserPass(const std::string &pass)
{
	this->userPass = pass;
}

void	User::setAuth(bool auth)
{
	this->auth = auth;
}

void	User::setHost(const std::string &host)
{
	this->host = host;
}

void	User::setRealname(const std::string &name)
{
	this->realname = name;
}

void	User::setPrefix(const std::string &prefix)
{
	this->prefix = prefix;
}

const std::string	&User::getNickname() const
{
	return (this->nickname);
}

const std::string	&User::getUsername() const
{
	return (this->username);
}

const std::string	&User::getUserPass() const
{
	return (this->userPass);
}

const std::string	&User::getServerPass() const
{
	return (this->serverPass);
}

int	User::getFd()
{
	return (this->fd);
}

bool	User::isAuth()
{
	return (this->auth);
}

const std::string	&User::getHost() const
{
	return (this->host);
}

const std::string	&User::getRealname() const
{
	return (this->realname);
}

const std::string	&User::getPrefix() const
{
	return (this->prefix);
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
	cmd[COMMAND] = command.substr(0, command.find("\r"));
}

std::map<int, std::string>	&User::getCommand()
{
	return (this->cmd);
}

void	User::clearCmdMap()
{
	this->cmd.erase(this->cmd.begin(), this->cmd.end());
}
