/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:27:02 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/01 15:29:08 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>

#define RPL_WELCOME(nick, user, host) (":localhost 001 HexChat ::Welcome to the ircserv Network, " + nick + "[!" + user + "@" + host + "]\r\n")