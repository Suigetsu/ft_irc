# FT_IRC
![irc gif](https://github.com/Suigetsu/ft_irc/assets/57911923/35a77d1d-e128-40fe-861b-8e72c647bcc5)

## Table of contents
1. [What is IRC?](https://github.com/Suigetsu/ft_irc?tab=readme-ov-file#what-is-irc)
2. The project's requirements
3. Implemented commands
4. Resources
5. Authors

## What is IRC?
IRC, short for Internet Relay Chat, is a text-based chat protocol that allows clients to communecate with other clients (or servers) over. IRC users connect to one of numerous networks and then join one or more of the channels.
### IRC CLIENT AND SERVER
- Servers:
  > a point to which clients may connect and talk to each other, and a point for other servers to connect to, forming an IRC network. [Read more](https://modern.ircdocs.horse/#servers)
- Client: Anything connecting to a server that is not another server.
## Requirements
* Develop an IRC server in C++ 98 without developing a client or a server-to-server communication.
* The executable will be run as follows: ```./ircserv <port> <password>```
* The server must be capable of handling multiple clients at the same time and never hang.
* Communication between client and server has to be done via TCP/IP (v4 or v6).
## Implemented commands
| Command name | Definition | Usage |
| ------------- | ------------- | ------------- |
| INVITE | The INVITE command is used to invite a user to a channel. | INVITE \<nickname\> \<channel\> |
| JOIN | The JOIN command is used by a user to request to start listening to the specific or multiple channels. You can leave all the channels by using 0 as a parameter | JOIN ( \<channel\> *( "," \<channel\> ) [ \<key\> *( "," \<key\> ) ] )/"0" |
| KICK | The KICK command can be used to request the forced removal of a user from one or multiple channels. | KICK \<channel\> *( "," \<channel\> ) \<user\> *( "," \<user\> ) [\<comment\>] |
| MODE (user) | The user MODE's are typically changes which affect either how the client is seen by others or what 'extra' messages the client is sent. | MODE \<nickname\> *( ( "+" / "-" ) *(modes) ) |
| MODE (channel) | The MODE command is provided so that users may query and change the characteristics of a channel. | MODE \<channel\> *( ( "-" / "+" ) *\<modes\> *\<modeparams\> ) |
| MOTD | The MOTD command is used to get the "Message Of The Day" of the given server | MOTD |
| NICK | NICK command is used to give user a nickname or change the existing one. | NICK \<nickname\> |
| PRIVMSG | PRIVMSG is used to send private messages between users, as well as to send messages to channels.  \<msgtarget\> is usually the nickname of the recipient of the message, or a channel name. | PRIVMSG \<msgtarget\> \<text to be sent\> |
| NOTICE | The NOTICE command is used similarly to PRIVMSG. The difference between NOTICE and PRIVMSG is that automatic replies MUST NEVER be sent in response to a NOTICE message. | NOTICE \<msgtarget\> \<text\> |
| PART | The PART command causes the user sending the message to be removed from the list of active members for all given channels listed in the parameter string. | PART \<channel\> *( "," \<channel\> ) [ \<Part Message\> ] |
| PASS | The PASS command is used to set a 'connection password'. The optional password can and MUST be set before any attempt to register the connection is made.  Currently this requires that user send a PASS command before sending the NICK/USER combination. | PASS \<password\> |
