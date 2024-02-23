/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:16:57 by mlagrini          #+#    #+#             */
/*   Updated: 2024/02/23 11:04:26 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() {}

Server::~Server() {}

const char	*Server::errorException::what() const throw()
{
	return ("The parameters you entered are wrong.");
}

void	Server::checkParameters(char **args)
{
	char *pEnd = NULL;

	errno = 0;
	const long i = std::strtol(args[1], &pEnd, 10);
	if (errno == ERANGE || errno == EINVAL || *pEnd)
		throw(Server::errorException());
	this->port = i;
	this->password = args[2];
}

long	Server::getPort() const
{
	return (this->port);
}

std::string	Server::getPassword() const
{
	return (this->password);
}

void	Server::createServerSocket()
{
	int status = 0;

	std::memset(&this->hints, 0, sizeof(this->hints));
	this->hints.ai_family = AF_INET;
	this->hints.ai_socktype = SOCK_STREAM;
	status = getaddrinfo(NULL, std::to_string(this->port).c_str(), &this->hints, &this->serverAddr);
	if (status != 0)
	{
		std::cout << "Error getting address info" << std::endl;
		throw(Server::errorException());
	}
	this->serverFd = socket(this->serverAddr->ai_family, this->serverAddr->ai_socktype, 0);
	if (this->serverFd == -1)
	{
		std::cerr << "Error creating socket" << std::endl;
		throw(Server::errorException());
	}
	int flag = 1;
	std::cout << "Socket has been created!" << std::endl;
	if (setsockopt(this->serverFd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int)) == -1)
	{
		perror("Setsocketopt");
		close(this->serverFd);
		freeaddrinfo(this->serverAddr);
		throw(Server::errorException());
	}
}

void	Server::bindSocket()
{
	errno = 0;
	int status = bind(this->serverFd, this->serverAddr->ai_addr, this->serverAddr->ai_addrlen);
	if (status != 0)
	{
		perror("Error binding socket");
		std::cout << "Binding error details; " << strerror(errno) << std::endl;
		close(this->serverFd);
		freeaddrinfo(this->serverAddr);
		throw(Server::errorException());
	}
	status = listen(this->serverFd, 10);
	if (status != 0)
	{
		perror("Error while listening for connections");
		close(this->serverFd);
		freeaddrinfo(this->serverAddr);
		throw(Server::errorException());
	}
	std::cout << "Server is listening on port " << port << "..." << std::endl;
}

void	Server::acceptConnection()
{
	struct sockaddr_in clientAddr = this->clientObj.getClientAddr();
	socklen_t addrSize = sizeof(this->clientObj.getClientAddr());
	this->clientObj.setClientFd(accept(this->serverFd, (struct sockaddr *)&clientAddr, &addrSize));
	if (this->clientObj.getClientFd() == -1)
	{
		perror("Error while accepting connection");
		throw(Server::errorException());
	}
	std::cout << "Connection accepted from " << inet_ntoa(this->clientObj.getClientAddr().sin_addr) << std::endl;
}

void	Server::parseCommands(std::string buffer, int clientFd)
{
	if (!buffer.find("CAP"))
	{
		User obj;
		this->usersMap[clientFd] = obj.clone(this->getPassword());
		return;
		// if (buffer.find("PASS"))
		// 	send(clientFd, "<client> :Password incorrect\r\n", 31, 0);
	}
	if (this->usersMap[clientFd]->isAuth() == false)
	{
		std::string line = buffer.substr(0, buffer.find("\r"));
		std::cout << "this is before erase:" << line << std::endl;
		line.erase(0, line.find(" ") + 1);
		this->usersMap[clientFd]->setUserPass(line);
		std::cout << "this is pass:" << line << std::endl;
	}
	Pass ptr;
	this->commandsMap["PASS"] = ptr.clone();
	this->commandsMap["PASS"]->execute(this->usersMap, clientFd);
}

void Server::initServer()
{
	int bread = 1;
	char buffer[1024];
	this->createServerSocket();
	this->bindSocket();
	this->acceptConnection();
	while (1)
	{
		bread = recv(this->clientObj.getClientFd(), buffer, 1000, 0);
		if (bread < 0)
		{
			perror("Error while reading from the client");
			throw(errorException());
		} else if (bread == 0)
		{
			std::cout << "connection closed by the client" << std::endl;
			break;
		} else
		{
			buffer[bread] = '\0';
			std::cout << buffer << std::endl;
			this->parseCommands(buffer, this->clientObj.getClientFd());
			std::cout << "-------" << std::endl;
		}
	}
	close(this->serverFd);
}

void Server::init(int port) {
	int clientSocket;
	struct addrinfo hints, *serverInfo;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	int status =
			getaddrinfo(NULL, std::to_string(port).c_str(), &hints, &serverInfo);
	if (status != 0) {
		std::cout << "Error getting address info" << std::endl;
		return;
	}
	int serverSocket = socket(serverInfo->ai_family, serverInfo->ai_socktype,
														serverInfo->ai_protocol);
	if (serverSocket == -1) {
		std::cerr << "Error creating socket" << std::endl;
		return;
	}
	std::cout << "Socket has been created!" << std::endl;

	int flag = 1;
	if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int)) ==
			-1) {
		perror("Setsocketopt");
		close(serverSocket);
		freeaddrinfo(serverInfo);
		return;
	}
	struct sockaddr_in clientAddress;
	socklen_t clientAddrLen = sizeof(clientAddress);
	if (bind(serverSocket, serverInfo->ai_addr, serverInfo->ai_addrlen)) {
		perror("Error binding socket");
		std::cout << "Binding error details; " << strerror(errno) << std::endl;
		close(serverSocket);
		return;
	}
	freeaddrinfo(serverInfo);

	if (listen(serverSocket, 10) == -1) {
		perror("Error while listening for connections");
		close(serverSocket);
		return;
	}
	std::cout << "Server is listening on port " << port << "..." << std::endl;
	while (1) {
		if ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress,
															 &clientAddrLen) == -1)) {
			perror("Error while accepting connection");
			continue;
		}
		std::cout << "Connection accepted from "
							<< inet_ntoa(clientAddress.sin_addr) << std::endl;
		char buffer[1024];
		int bread;
		bread = recv(clientSocket, buffer, sizeof(buffer), 0);
		if (bread == -1)
			perror("Error while reading from the client");
		else if (bread == 0)
			std::cout << "connection closed by the client" << std::endl;
		else {
			std::cout << "Recieved data from the client: " << buffer << std::endl;
			const char *resp =
					"Hello, client! This is server! I recieved your message!";
			send(clientSocket, resp, strlen(resp), 0);
		}
		close(clientSocket);
	}
	close(serverSocket);
}
