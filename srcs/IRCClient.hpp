/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCClient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:34:21 by mlagrini          #+#    #+#             */
/*   Updated: 2024/02/11 15:36:41 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCCLIENT_HPP
# define IRCCLIENT_HPP

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

class	Client
{
	private:
		struct sockaddr *clientAddr;
};

#endif
