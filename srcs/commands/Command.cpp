/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:22:39 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/04 16:35:39 by hrahmane         ###   ########.fr       */
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
