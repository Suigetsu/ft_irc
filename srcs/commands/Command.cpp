/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:22:39 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/03 14:37:13 by mlagrini         ###   ########.fr       */
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

