/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:43:38 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/07 11:31:05 by hrahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <sstream>
# include <sys/socket.h>
# include <unistd.h>
# include <netdb.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <csignal>
# include <sys/stat.h>
# include <fcntl.h>
# include <map>
# include <iterator>
# include <vector>
# include "RPL.hpp"
# include "ERR.hpp"
# include "Command.hpp"
# include "Client.hpp"
# include "Pass.hpp"
# include "User.hpp"
# include "Nick.hpp"
# include "UserCmd.hpp"
# include "Quit.hpp"
# include "Ping.hpp"
# include "Channel.hpp"
# include "poll.h"

# define BACKLOG 10
# define COMMAND 0
# define FIRST_PARAM 1
# define SECOND_PARAM 2
# define THIRD_PARAM 3

class	Server
{
	private:
		int	port;
		std::string password;
		struct addrinfo hints;
		struct addrinfo *serverAddr;
		struct sockaddr_in servAddr;
		// int status;
		int	serverFd;
		Client clientObj;
		std::vector<std::string> parser;
		std::map<int, User *> usersMap;
		std::map<std::string, Channel *> channels;
		std::map<std::string, Command *> commandsMap;
		std::vector<struct pollfd> fds;
		std::vector<int> registeredFds;
	public:
		static bool status;
		static void signalHandler(int signum);
		Server();
		Server(const Server &obj);
		Server	&operator=(const Server &obj);
		~Server();
		void	checkParameters(char **args);
		void	init(int port);
		class	errorException : public std::exception
		{
			public:
				const char *what() const throw();
		};
		template <typename T>
		void	registerCommand(std::string commandName)
		{
			this->commandsMap[commandName] = new T;
		}
		template <typename T>
		void	deleteMaps(T &map)
		{
			typename T::iterator it = map.begin();
			while (it != map.end())
			{
				if (it->second)
					delete it->second;
				it++;
			}
		}
		long	getPort() const;
		std::string	getPassword() const;
		void	initServer();
		void	createServerSocket();
		void	bindSocket();
		void	acceptConnection();
		void	registerUser(std::string buffer, int clientFd);
		bool	isRegistered(int fd);
		void	addUser(int fd);
		void	closeFds();
		bool    doesChannelExist(const std::string &name);
		void	joinChannel(User user, const std::string &name);
		void	handleRegisteredCommand(std::string command, int fd);
		bool	doesCommandExist(std::string cmdName);
		void	launchCommand(std::map<int, std::string>cmd, int fd);
};


#endif
