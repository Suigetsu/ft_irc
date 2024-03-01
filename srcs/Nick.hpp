/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:47:53 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/01 15:31:08 by mlagrini         ###   ########.fr       */
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
		void	execute(std::map<int, User *> userMap, int clientFd) const;
		Nick	*clone() const;
		bool	doesNameExist(std::map<int, User *> userMap, std::string name) const;
		bool	containsRestrictedChar(std::string name) const;
};