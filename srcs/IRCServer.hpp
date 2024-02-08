/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:43:38 by mlagrini          #+#    #+#             */
/*   Updated: 2024/02/08 18:08:36 by mlagrini         ###   ########.fr       */
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

# define PORT 0
# define PASSWORD 1

class	IRCServer
{
	private:
		std::map<int, long> PortPasswordMap;
	public:
		IRCServer();
		IRCServer(const IRCServer &obj);
		IRCServer	&operator=(const IRCServer &obj);
		~IRCServer();
		void	checkParameters(char **args);
		class	errorException : public std::exception
		{
			public:
				const char *what() const throw();
		};
};


#endif
