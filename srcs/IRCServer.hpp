/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:43:38 by mlagrini          #+#    #+#             */
/*   Updated: 2024/02/15 17:16:18 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERVER_HPP
# define IRCSERVER_HPP

# include <iostream>
# include <sys/socket.h>
# include <unistd.h>
# include <netdb.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <map>
# include <iterator>
# include "IRCClient.hpp"

class	IRCServer
{
	private:
		int	port;
		std::string password;
		// struct addrinfo hints;
		// struct addrinfo *serverAddr;
		struct sockaddr_in servAddr;
		int status;
		int	serverFd;
		Client clientObj;
	public:
		IRCServer();
		IRCServer(const IRCServer &obj);
		IRCServer	&operator=(const IRCServer &obj);
		~IRCServer();
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
		// void	
};


#endif
