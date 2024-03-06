/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:27:02 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/05 17:17:41 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>

#define RPL_WELCOME(nick, user, host) (":localhost 001 HexChat :Welcome to the ircserv Network, :" + nick + "!" + user + "@" + host + "\r\n")
#define RPL_YOURHOST ":localhost 002 HexChat :Your host is ircserv (localhost), running version 1.2\r\n"
#define RPL_CREATED ":localhost 003 HexChat :This server was created Tue Mar 5 2024 3:48:54\r\n"
#define RPL_MYINFO ":localhost 004 HexChat ircserv 1.2 itkol\r\n"
#define RPL_ISUPPORT ":localhost 005 HexChat CASEMAPPING=ascii CHANNELLEN=50 CHANTYPES=# KICKLEN=255 CHANLIMIT=#50 CHANMODES=o,k,l,it NICKLEN=9 TOPICLEN=490 :are supported by this server\r\n"
#define QUIT_MSG(nick, user, host, reason) (":" + nick + "!" + user + "@" + host + " QUIT :Quit: " + reason + "\r\n")