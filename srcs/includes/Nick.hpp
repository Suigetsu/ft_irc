/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:47:53 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/09 10:07:26 by mlagrini         ###   ########.fr       */
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
		void	execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const;
		Nick	*clone() const;
		bool	doesNameExist(std::map<int, User *> userMap, std::string name) const;
		bool	containsRestrictedChar(std::string name) const;
};