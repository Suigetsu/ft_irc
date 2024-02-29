/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:24:40 by mlagrini          #+#    #+#             */
/*   Updated: 2024/02/29 18:20:05 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "User.hpp"
#include "Command.hpp"

#define ERR_PASSWDMISMATCH ":localhost 464 HexChat :Password incorrect\r\n"

class Command;

class	Pass : public Command
{
	public:
		Pass();
		~Pass();
		void	execute(std::map<int, User *> userMap, int clientFd) const;
		Pass	*clone() const;
};