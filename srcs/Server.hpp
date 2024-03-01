/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:43:38 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/01 11:49:33 by hrahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
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
# include "Command.hpp"
# include "Client.hpp"
# include "Pass.hpp"
# include "User.hpp"
# include "Channel.hpp"
# include "poll.h"
# define BACKLOG 10

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
		std::map<std::string, std::vector<int> > channels;
		std::map<std::string, Command *> commandsMap;
		std::vector<struct pollfd> fds;
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
		long	getPort() const;
		std::string	getPassword() const;
		void	initServer();
		void	createServerSocket();
		void	bindSocket();
		void	acceptConnection();
		void	parseCommands(std::string buffer, int clientFd);
		void	createChannel(const std::string &name);
		void	joinChannel(int id, const std::string &name);
		void	leaveChannel(int id, const std::string &name);
};


#endif
