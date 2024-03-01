/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:16:57 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/01 11:45:17 by hrahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool Server::status = false;

void	Server::signalHandler(int signum)
{
	if (signum == SIGINT)
		std::cout << "We received SIGINT" << std::endl;
	else if (signum == SIGQUIT)
		std::cout << "This is SIGQUIT" << std::endl;
	Server::status = true;
}

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
	struct pollfd npoll;

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
	fcntl(this->serverFd, F_SETFL, O_NONBLOCK);
	if (this->serverFd == -1)
	{
		std::cout << "Error creating socket" << std::endl;
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
	npoll.fd = this->serverFd;
	npoll.events = POLLIN;
	npoll.revents = 0;
	this->fds.push_back(npoll);
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
	status = listen(this->serverFd, BACKLOG);
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
	fcntl(this->clientObj.getClientFd(), F_SETFL, O_NONBLOCK);
	if (this->clientObj.getClientFd() == -1)
	{
		perror("Error while accepting connection");
		throw(Server::errorException());
	}
	std::cout << "Connection accepted from " << inet_ntoa(this->clientObj.getClientAddr().sin_addr) << std::endl;
	struct pollfd poll;
	poll.fd = this->clientObj.getClientFd();
	poll.events = POLLIN;
	poll.revents = 0;
	this->fds.push_back(poll);
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
	// this->acceptConnection();
	while (!Server::status)
	{
		if (poll(&this->fds[0], this->fds.size(), -1) == -1 && !Server::status)
		{
			perror("poll failed");
			throw(errorException());
		}
		for (size_t i = 0; i < this->fds.size(); i++)
		{
			if (this->fds[i].revents & POLLIN)
			{
				if (this->fds[i].fd == this->serverFd)
					this->acceptConnection();
				else
				{
					bread = recv(this->fds[i].fd, buffer, 1000, 0);
					if (bread < 0)
					{
						perror("Error while reading from the client");
						throw(errorException());
					} else if (bread == 0)
					{
						std::cout << "connection closed by the client" << std::endl;
						close(this->fds[i].fd);
						break;
					} else
					{
						buffer[bread] = '\0';
						std::cout << buffer << std::endl;
						// this->parseCommands(buffer, this->fds[i].fd);
						std::cout << "-------" << std::endl;
					}
					sleep(2);
				}
			}
		}
	}
	// while (1)
	// {
	// 	bread = recv(this->clientObj.getClientFd(), buffer, 1000, 0);
	// 	if (bread < 0)
	// 	{
	// 		perror("Error while reading from the client");
	// 		throw(errorException());
	// 	} else if (bread == 0)
	// 	{
	// 		std::cout << "connection closed by the client" << std::endl;
	// 		break;
	// 	} else
	// 	{
	// 		buffer[bread] = '\0';
	// 		std::cout << buffer << std::endl;
	// 		this->parseCommands(buffer, this->clientObj.getClientFd());
	// 		std::cout << "-------" << std::endl;
	// 	}
	// }
	close(this->serverFd);
}

void	Server::createChannel(const std::string &name)
{
	if (!name.empty() && name.find_first_of("&#+!") == 0)
	{
		if (name.length() <= 50)
		{
			if (this->channels.find(name) == this->channels.end())
			{
				// channels[name] = std::vector<int>();
				std::cout << "Channel " << name << " has been created." << std::endl;
			}
			else
				std::cout << "Channel " << name << "already exists." << std::endl;
		}
		else
			std::cout << "Channel name should not exceed 50 chars." << std::endl;
	}
	else
		std::cout << "Invalid channel name." << std::endl;
}

void	Server::joinChannel(int id, const std::string &name)
{
	if (channels.find(name) == channels.end())
	{
		std::cout << "Channel " << name << " does not exist." << std::endl;
		return ;
	}
	if (std::find(channels[name].begin(), channels[name].end(), id) == channels[name].end())
	{
		
	}
}

void	Server::leaveChannel(int id, const std::string &name)
{
	
}

