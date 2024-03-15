/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:05:13 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/15 13:13:48 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "User.hpp"
#include "Command.hpp"

class Command;

class	Who : public Command
{
	public:
		Who();
		~Who();
		void	execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const;
		void	sendWho(User *usr, Channel *chan, int fd) const;
		Who	*clone() const;
};