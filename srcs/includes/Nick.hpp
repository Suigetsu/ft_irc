/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:47:53 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/04 16:33:15 by hrahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "User.hpp"
#include "Command.hpp"

class Nick : public Command
{
	public:
		Nick();
		~Nick();
		void	execute(std::map<int, User *> userMap, std::map<std::string, Channel *> chan, int clientFd) const;
		Nick	*clone() const;
		bool	doesNameExist(std::map<int, User *> userMap, std::string name) const;
		bool	containsRestrictedChar(std::string name) const;
};