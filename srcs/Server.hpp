/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:43:38 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/01 16:56:21 by mlagrini         ###   ########.fr       */
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
# include "RPL.hpp"
# include "ERR.hpp"
# include "Command.hpp"
# include "Client.hpp"
# include "Pass.hpp"
# include "User.hpp"
# include "Nick.hpp"
# include "Channel.hpp"
>>>>>>>>> Temporary merge branch 2
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
		void	createChannel(const std::string &name);
		void	joinChannel(int id, const std::string &name);
		void	leaveChannel(int id, const std::string &name);
		bool	isRegistered(int fd);
		void	addUser(int fd);
		void	closeFds();
};


#endif
