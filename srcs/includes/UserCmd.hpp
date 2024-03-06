/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:30:10 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/05 12:57:18 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "User.hpp"
#include "Command.hpp"

class UserCmd : public Command
{
	public:
		UserCmd();
		~UserCmd();
		void	execute(std::map<int, User *> userMap, std::map<std::string, Channel *> chan, int clientFd) const;
		UserCmd	*clone() const;
		bool	doesNameExist(std::map<int, User *> userMap, std::string name) const;
		bool	containsRestrictedChar(std::string name) const;
		std::vector<std::string>	parseParams(std::map<int, std::string> cmd, int fd) const;
};