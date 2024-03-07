/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:27:02 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/07 09:57:11 by hrahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>

#define RPL_WELCOME(nick, user, host) (":localhost 001 " + nick + " :Welcome to the ft_irc Network " + nick + "!" + user + "@" + host + "\r\n")
#define RPL_YOURHOST(nick) ":localhost 002 " + nick + " :Your host is ircserv (localhost), running version 1.2\r\n"
#define RPL_CREATED(nick) ":localhost 003 " + nick + " :This server was created Tue Mar 5 2024 3:48:54\r\n"
#define RPL_MYINFO(nick) ":localhost 004 " + nick + " ircserv 1.2 itkol\r\n"
#define RPL_ISUPPORT(nick) ":localhost 005 " + nick + " CASEMAPPING=ascii CHANNELLEN=50 CHANTYPES=# KICKLEN=255 CHANLIMIT=#50 CHANMODES=o,k,l,it NICKLEN=9 TOPICLEN=490 :are supported by this server\r\n"
#define QUIT_MSG(nick, user, host, reason) (":" + nick + "!" + user + "@" + host + " QUIT :Quit: " + reason + "\r\n")