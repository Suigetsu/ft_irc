/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:27:02 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/16 11:24:24 by hrahmane         ###   ########.fr       */
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
#define RPL_MOTDSTART(nick) ":localhost 375 " + nick + " :- ircserv Message of the day - \r\n"
#define RPL_MOTD(nick, motd) ":localhost 372 " + nick + " :" + motd + "\r\n"
#define RPL_ENDOFMOTD(nick) ":localhost 376 " + nick + " :End of MOTD command\r\n"
#define QUIT_MSG(nick, user, host, reason) (":" + nick + "!" + user + "@" + host + " QUIT :Quit: " + reason + "\r\n")
#define RPL_NAMREPLY(nick, user, chan, host, list, prefix) (":localhost 353 " + nick + " = " + chan + " :" + prefix + nick + "!" + user + "@" + host + " " + list + "\r\n")
#define JOIN(nick, user, host, chan) (":" + nick + "!" + user + "@" + host + " JOIN " + chan + "\r\n")
#define MODE(nick, user, host, chan, mode) (":" + nick + "!" + "@" + host + " MODE " + chan + " " + mode + "\r\n")
#define RPL_ENDOFNAMES(nick, chan) (":localhost 366 " + nick + " " + chan + " :End of /NAMES list\r\n")
#define RPL_CHANNELMODEIS(nick, chan, modes) (":localhost 324 " + nick + " " + chan + " " + modes + "\r\n")