/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Motd.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:40:13 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/16 12:43:46 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "User.hpp"
#include "Command.hpp"
#include <fstream>

class Command;

class	Motd : public Command
{
	public:
		Motd();
		~Motd();
		void	execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const;
		Motd	*clone() const;
};