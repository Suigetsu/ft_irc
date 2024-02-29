/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:47:53 by mlagrini          #+#    #+#             */
/*   Updated: 2024/02/29 18:22:10 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "User.hpp"
#include "Command.hpp"

#define ERR_NONICKNAMEGIVEN ":localhost 431 HexChat :No nickname given\r\n"
#define ERR_ERRONEUSNICKNAME(nick) (":localhost 432 HexChat " + nick + " :Erroneus nickname\r\n")
#define ERR_NICKNAMEINUSE(nick) (":localhost 433 HexChat " + nick + " :Nickname is already in use\r\n")

class Nick : public Command
{
	public:
		Nick();
		~Nick();
		void	execute(std::map<int, User *> userMap, int clientFd) const;
		Nick	*clone() const;
		bool	doesNameExist(std::map<int, User *> userMap, std::string name) const;
		bool	containsRestrictedChar(std::string name) const;
};