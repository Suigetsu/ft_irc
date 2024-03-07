/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:09:34 by hrahmane          #+#    #+#             */
/*   Updated: 2024/03/07 11:22:09 by hrahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "User.hpp"
#include "Pong.hpp"
#include "Command.hpp"

class Command;

class	Ping : public Command
{
	public:
		Ping();
		~Ping();
		void	execute(std::map<int, User *> userMap, std::map<std::string, Channel *> chan, int clientFd) const;
		Ping	*clone() const;
};