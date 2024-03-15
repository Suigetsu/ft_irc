/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WhoIs.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:00:25 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/15 15:39:01 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "User.hpp"
#include "Command.hpp"

class Command;

class	WhoIs : public Command
{
	public:
		WhoIs();
		~WhoIs();
		void	execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const;
		void	sendWhoIs(User *client, User *whoUsr, std::map<std::string, Channel *> &chan, int fd) const;
		User	*getUser(std::map<int, User *> &users, const std::string &name) const;
		std::string	getWhoIsChannelsBuffer(std::map<std::string, Channel *> &chan, std::string nick) const;
		WhoIs	*clone() const;
};