/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:29:57 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/02 14:25:02 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>

#define ERR_PASSWDMISMATCH ":localhost 464 HexChat :Password incorrect\r\n"
#define ERR_NONICKNAMEGIVEN ":localhost 431 HexChat :No nickname given\r\n"
#define ERR_ERRONEUSNICKNAME(nick) (":localhost 432 HexChat " + nick + " :Erroneus nickname\r\n")
#define ERR_NICKNAMEINUSE(nick) (":localhost 433 HexChat " + nick + " :Nickname is already in use\r\n")
#define ERR_NEEDMOREPARAMS ":localhost 461 HexChat USER :Not enough parameters\r\n"
#define ERR_UNKNOWNCOMMAND(command) (":localhost 421 HexChat " + command + " :Unknown command\r\n")
