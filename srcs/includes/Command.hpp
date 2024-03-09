/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:21:08 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/09 10:07:26 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>
#include "User.hpp"
#include "Channel.hpp"
#include "RPL.hpp"
#include "ERR.hpp"

class	Command
{
	public:
		Command();
		virtual ~Command();
		virtual void	execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const = 0;
		virtual Command	*clone() const = 0;
		class	registrationException : public std::exception
		{
			public:
				const char *what() const throw();
		};
		class	unknownCommandException : public std::exception
		{
			public:
				const char *what() const throw();
		};
};