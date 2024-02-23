/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:24:40 by mlagrini          #+#    #+#             */
/*   Updated: 2024/02/22 19:34:10 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "User.hpp"
#include "Command.hpp"

class Command;

class	Pass : public Command
{
	public:
		Pass();
		~Pass();
		void	execute(std::map<int, User *> userMap, int clientFd) const;
		Pass	*clone() const;
};