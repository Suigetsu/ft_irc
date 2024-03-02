/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:34:21 by mlagrini          #+#    #+#             */
/*   Updated: 2024/02/22 19:36:46 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <sys/socket.h>
# include <netinet/in.h>
# include <map>
# include <iterator>

class	Client
{
	private:
		struct sockaddr_in clientAddr;
		int clientFd; 
	public:
		Client();
		~Client();
		void	setAddr(struct sockaddr_in addr);
		void	setClientFd(int fd);
		struct sockaddr_in getClientAddr();
		int	getClientFd();
};

#endif
