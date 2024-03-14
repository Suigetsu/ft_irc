/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:25:20 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/13 15:42:34 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "User.hpp"
#include "Command.hpp"

class Command;

class	Topic : public Command
{
	public:
		Topic();
		~Topic();
		void	execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const;
		std::vector<std::string> parseTopic(std::string command) const;
		void	sendTopic(Channel *chan, User *user, int fd) const;
		void	setTopic(User *user, Channel **chan, std::string topic, int fd) const;
		Topic	*clone() const;
};