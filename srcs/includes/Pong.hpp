/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:19:37 by hrahmane          #+#    #+#             */
/*   Updated: 2024/03/07 11:22:05 by hrahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "User.hpp"
#include "Command.hpp"

class Command;

class	Pong : public Command
{
	public:
		Pong();
		~Pong();
		void	execute(std::map<int, User *> userMap, std::map<std::string, Channel *> chan, int clientFd) const;
		Pong	*clone() const;
};