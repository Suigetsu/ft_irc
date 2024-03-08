/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:29:57 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/07 12:46:09 by hrahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>

#define ERR_PASSWDMISMATCH ":localhost 464 HexChat :Password incorrect\r\n"
#define ERR_NONICKNAMEGIVEN ":localhost 431 HexChat :No nickname given\r\n"
#define ERR_ERRONEUSNICKNAME(nick) (":localhost 432 HexChat " + nick + " :Erroneus nickname\r\n")
#define ERR_NICKNAMEINUSE(nick) (":localhost 433 HexChat " + nick + " :Nickname is already in use\r\n")
#define ERR_NEEDMOREPARAMS(cmd) (":localhost 461 HexChat " + cmd + " :Not enough parameters\r\n")
#define ERR_UNKNOWNCOMMAND(command) (":localhost 421 HexChat " + command + " :Unknown command\r\n")
#define ERR_NOTEXTTOSEND ":localhost 412 HexChat :No text to send\r\n"
#define ERR_NORECIPIENT(command) (":localhost 411 HexChat :No recipient given (" + command + ")\r\n")
#define ERR_ALREADYREGISTERED ":localhost 462 HexChat :You may not reregister\r\n"
#define ERR_NOMOTD ":localhost 422 HexChat :MOTD File is missing\r\n"