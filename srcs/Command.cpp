/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:22:39 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/01 15:37:03 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

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
