/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:21:08 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/04 16:30:33 by hrahmane         ###   ########.fr       */
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
		virtual void	execute(std::map<int, User *> userMap, std::map<std::string, Channel *> chan, int clientFd) const = 0;
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