/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:29:57 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/09 19:18:24 by hrahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>

#define ERR_PASSWDMISMATCH ":localhost 464 HexChat :Password incorrect\r\n"
#define ERR_NONICKNAMEGIVEN ":localhost 431 HexChat :No nickname given\r\n"
#define ERR_ERRONEUSNICKNAME(nick) (":localhost 432 " + nick + " " + nick + " :Erroneus nickname\r\n")
#define ERR_NICKNAMEINUSE(nick) (":localhost 433 " + nick + " " + nick + " :Nickname is already in use\r\n")
#define ERR_NEEDMOREPARAMS(nick, cmd) (":localhost 461 " + nick + " " + cmd + " :Not enough parameters\r\n")
#define ERR_UNKNOWNCOMMAND(nick, command) (":localhost 421 " + nick + " " + command + " :Unknown command\r\n")
#define ERR_NOTEXTTOSEND(nick) (":localhost 412 " + nick + " :No text to send\r\n")
#define ERR_NORECIPIENT(nick, command) (":localhost 411 " + nick + " :No recipient given (" + command + ")\r\n")
#define ERR_ALREADYREGISTERED(nick) (":localhost 462 " + nick + " :You may not reregister\r\n")
#define ERR_NOMOTD(nick) (":localhost 422 " + nick + " :MOTD File is missing\r\n")
#define ERR_NOSUCHCHANNEL(nick, chan) (":localhost 403 " + nick + " " + chan + " :No such channel\r\n")
#define ERR_CHANNELISFULL(nick, chan) (":localhost 471 " + nick + " " + chan + " :Cannot join channel (+l)\r\n")
#define ERR_INVITEONLYCHAN(nick, chan) (":localhost 473 " + nick + " " + chan + " :Cannot join channel (+i)\r\n")
#define ERR_BADCHANNELKEY(nick, chan) (":localhost 475 " + nick + " " + chan + " :Cannot join channel (+k)\r\n")
#define ERR_NOSUCHCHANNEL(nick, chan) (":localhost 403 " + nick + " " + chan + " :No such channel\r\n")