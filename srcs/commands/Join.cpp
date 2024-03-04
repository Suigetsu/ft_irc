/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:01:56 by hrahmane          #+#    #+#             */
/*   Updated: 2024/03/04 16:42:37 by hrahmane         ###   ########.fr       */
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
	
}

Join	*Join::clone() const
{
	return (new Join);
}