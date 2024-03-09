/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:09:34 by hrahmane          #+#    #+#             */
/*   Updated: 2024/03/09 10:07:26 by mlagrini         ###   ########.fr       */
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
		void	execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const;
		Ping	*clone() const;
};