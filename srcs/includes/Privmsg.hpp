/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:52:00 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/16 16:04:11 by mlagrini         ###   ########.fr       */
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
		void	execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const;
		void	parseInput(std::vector<std::string> &recipVec, std::string &text, std::string param) const;
		std::vector<std::string>	getRecipients(const std::string &list) const;
		void	sendMsg(std::map<int, User *> &, std::map<std::string, Channel *> &, int, std::vector<std::string>, std::string) const;
		int	doesUserExist(std::map<int, User *> &usrs, std::string nick) const;
		bool	doesChanExist(std::map<std::string, Channel *> &chan, std::string name) const;
		void	bufferizeChan(User *user, std::map<std::string, Channel *> &chan, std::string recp, std::string text, int fd) const;
		void	bufferizeUser(User *user, std::map<int, User *> &users, std::string recp, std::string text, int fd) const;
		Privmsg	*clone() const;
};