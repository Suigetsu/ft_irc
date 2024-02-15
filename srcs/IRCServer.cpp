/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:16:57 by mlagrini          #+#    #+#             */
/*   Updated: 2024/02/15 12:28:40 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCServer.hpp"

IRCServer::IRCServer()
{
	
}

IRCServer::~IRCServer()
{

}

const char	*IRCServer::errorException::what() const throw()
{
	return ("The parameters you entered are wrong.");
}

void	IRCServer::checkParameters(char **args)
{
	char *pEnd = NULL;
	
	errno = 0;
	const long i = std::strtol(args[1], &pEnd, 10);
	if (errno == ERANGE || errno == EINVAL || *pEnd)
		throw (IRCServer::errorException());
	this->port = i;
	this->password = args[2];
}

long	IRCServer::getPort() const
{
	return (this->port);
}

std::string	IRCServer::getPassword() const
{
	return (this->password);
}
void IRCServer::init(int port)
{
    int clientSocket;
    struct addrinfo hints, *serverInfo;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    int status = getaddrinfo(NULL, std::to_string(port).c_str(), &hints, &serverInfo);
    if (status != 0)
    {
        std::cout << "Error getting address info" << std::endl;
        return;
    }
    int serverSocket = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);
    if (serverSocket == -1)
    {
        std::cerr << "Error creating socket" << std::endl;
        return ;
    }
    std::cout << "Socket has been created!" << std::endl;
    
    int flag = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int)) == -1)
    {
        perror("Setsocketopt");
        close(serverSocket);
        freeaddrinfo(serverInfo);
        return ;
    }
    struct sockaddr_in clientAddress;
    socklen_t clientAddrLen = sizeof(clientAddress);
    if (bind(serverSocket, serverInfo->ai_addr, serverInfo->ai_addrlen))
    {
        perror("Error binding socket");
        std::cout << "Binding error details; " << strerror(errno) << std::endl;
        close(serverSocket);
        return ;
    }
    freeaddrinfo(serverInfo);

    if (listen(serverSocket, PENDLOGS) == -1)
    {
        perror("Error while listening for connections");
        close(serverSocket);
        return ;
    }
    std::cout << "Server is listening on port " << port << "..." << std::endl;
    while (1)
    {
        if ((clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddrLen) == -1))
        {
            perror("Error while accepting connection");
            continue ;
        }
        std::cout << "Connection accepted from " << inet_ntoa(clientAddress.sin_addr) << std::endl;
        char buffer[1024];
        int bread;
        bread = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bread == -1)
            perror("Error while reading from the client");
        else if (bread == 0)
            std::cout << "connection closed by the client" << std::endl;
        else
        {
            std::cout << "Recieved data from the client: " << buffer << std::endl;
            const char *resp = "Hello, client! This is server! I recieved your message!";
            send(clientSocket, resp, strlen(resp), 0);
        }
        close(clientSocket);
    }
    close(serverSocket);
}
