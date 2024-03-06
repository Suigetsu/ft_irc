/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:52:00 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/04 18:13:52 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "User.hpp"
#include "Command.hpp"

class Command;

class	Privmsg : public Command
{
	public:
		Privmsg();
		~Privmsg();
		void	execute(std::map<int, User *> userMap, std::map<std::string, Channel *> chan, int clientFd) const;
		Privmsg	*clone() const;
};