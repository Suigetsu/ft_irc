/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:01:24 by hrahmane          #+#    #+#             */
/*   Updated: 2024/03/07 17:01:14 by hrahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "User.hpp"
#include "Command.hpp"
#include <string>
#include <iostream>

class Command;

class	Join : public Command
{
	private:
		std::vector<std::string> chans;
		std::vector<std::string> keys;
	public:
		Join();
		~Join();
		void	setChans(const std::string &list);
		void	setKeys(const std::string &list);
		const std::vector<std::string> &getChans() const;
		const std::vector<std::string> &getKeys() const;
		void	execute(std::map<int, User *> userMap, std::map<std::string, Channel *> chan, int clientFd) const;
		Join	*clone() const;
		bool	isNameValid(const std::string &name) const;
		void	parseChannels(std::string param);
};