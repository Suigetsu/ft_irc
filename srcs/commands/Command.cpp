/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:22:39 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/02 16:50:32 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

Command::Command()
{
	
}

Command::~Command()
{

}

const char  *Command::registrationException::what() const throw()
{
    return ("Registration failed");
}

const char  *Command::unknownCommandException::what() const throw()
{
    return ("Unknown command");
}

void    Command::setName(std::string name)
{
    this->name = name;
}

const std::string   Command::getName() const
{
    return (this->name);
}
