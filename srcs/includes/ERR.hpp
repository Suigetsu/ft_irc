#pragma once

#include <string>
#include <iostream>

#define ERR_PASSWDMISMATCH ":localhost 464 HexChat :Password incorrect\r\n"
#define ERR_NONICKNAMEGIVEN ":localhost 431 HexChat :No nickname given\r\n"
#define ERR_ERRONEUSNICKNAME(nick) (":localhost 432 " + nick + " " + nick + " :Erroneus nickname\r\n")
#define ERR_NICKNAMEINUSE(nick) (":localhost 433 " + nick + " " + nick + " :Nickname is already in use\r\n")
#define ERR_NEEDMOREPARAMS(nick, cmd) (":localhost 461 " + nick + " " + cmd + " :Not enough parameters\r\n")
#define ERR_UNKNOWNCOMMAND(nick, command) (":localhost 421 " + nick + " " + command + " :Unknown command\r\n")
#define ERR_ALREADYREGISTERED(nick) (":localhost 462 " + nick + " :You may not reregister\r\n")
#define ERR_NOMOTD(nick) (":localhost 422 " + nick + " :MOTD File is missing\r\n")
#define ERR_NOSUCHCHANNEL(nick, chan) (":localhost 403 " + nick + " " + chan + " :No such channel\r\n")
#define ERR_CHANNELISFULL(nick, chan) (":localhost 471 " + nick + " " + chan + " :Cannot join channel (+l)\r\n")
#define ERR_INVITEONLYCHAN(nick, chan) (":localhost 473 " + nick + " " + chan + " :Cannot join channel (+i)\r\n")
#define ERR_BADCHANNELKEY(nick, chan) (":localhost 475 " + nick + " " + chan + " :Cannot join channel (+k)\r\n")
#define ERR_NOSUCHCHANNEL(nick, chan) (":localhost 403 " + nick + " " + chan + " :No such channel\r\n")
#define ERR_UNKNOWNMODE(nick, mode) (":localhost 472 " + nick + " " + mode + " :Is unknown mode char to me\r\n")
#define ERR_NOSUCHNICK(nick, arg) (":localhost 401 " + nick + " " + arg + " :No such nick\r\n")
#define ERR_KEYSET(nick, chan) (":localhost 467 " + nick + " " + chan + " :Channel key already set\r\n")
#define ERR_CHANOPRIVSNEEDED(nick, chan) (":localhost 482 " + nick + " " + chan + " :You're not channel operator\r\n")
#define ERR_NOTONCHANNEL(nick, chan) (":localhost 442 " + nick + " " + chan + " :You're not on that channel\r\n")
#define ERR_CANNOTSENDTOCHAN(nick, chan) (":localhost 404 " + nick + " " + chan + " :Cannot send to channel\r\n")
#define ERR_NORECIPIENT(nick) (":localhost 411 " + nick + " :No recipient given (PRIVMSG)\r\n")
#define ERR_NOTEXTTOSEND(nick) (":localhost 412 " + nick + " :No text to send")
#define ERR_USERONCHANNEL(client, nick, chan) (":localhost 443 " + client + " " + nick + " " + chan + " :is already on channel\r\n")
#define LONG_MESSAGE(client) (":localhost " + client + " :Cannot send the message.\r\n")
#define ERR_USERNOTINCHANNEL(client, nick, chan) (":localhost 441 " + client + " " + nick + " " + chan + " :They aren't on that channel\r\n")
