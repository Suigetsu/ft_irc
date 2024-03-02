/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:21:08 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/01 15:36:10 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>
#include "User.hpp"
#include "RPL.hpp"
#include "ERR.hpp"

class	Command
{
	protected:
		std::string name;
	public:
		Command();
		virtual ~Command();
		virtual void	execute(std::map<int, User *> userMap, int clientFd) const = 0;
		virtual Command	*clone() const = 0;
		class	registrationException : public std::exception
		{
			public:
				const char *what() const throw();
		};
};