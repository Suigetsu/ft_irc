#include "./includes/Server.hpp"

bool 	Server::status = false;

void	Server::signalHandler(int signum)
{
	if (signum == SIGINT || signum == SIGQUIT)
		std::cout << "The server is closed." << std::endl;
	Server::status = true;
}

Server::Server()
{
	this->registerCommand<Pass>("PASS");
	this->registerCommand<Nick>("NICK");
	this->registerCommand<UserCmd>("USER");
	this->registerCommand<Quit>("QUIT");
	this->registerCommand<Ping>("PING");
	this->registerCommand<Join>("JOIN");
	this->registerCommand<Mode>("MODE");
	this->registerCommand<Topic>("TOPIC");
	this->registerCommand<Who>("WHO");
	this->registerCommand<WhoIs>("WHOIS");
	this->registerCommand<Motd>("MOTD");
	this->registerCommand<Privmsg>("PRIVMSG");
	this->registerCommand<Invite>("INVITE");
	this->registerCommand<Part>("PART");
	this->registerCommand<Kick>("KICK");
	this->registerCommand<Notice>("NOTICE");
}

Server::~Server()
{
	this->deleteMaps(this->commandsMap);
	this->deleteMaps(this->channels);
	this->deleteMaps(this->usersMap);
}

const char	*Server::errorException::what() const throw()
{
	return ("The parameters you entered are wrong.");
}

void		Server::checkParameters(char **args)
{
	char 		*pEnd = NULL;
	const long	i = std::strtol(args[1], &pEnd, 10);
	errno = 0;

	if (errno == ERANGE || errno == EINVAL || *pEnd)
		throw(Server::errorException());
	this->port = i;
	this->portString = args[1];
	this->password = args[2];
}

std::string	Server::getPassword() const { return (this->password); }

long		Server::getPort() const { return (this->port); }

void		Server::createServerSocket()
{
	struct pollfd	npoll;
	int 			status = 0;

	std::memset(&this->hints, 0, sizeof(this->hints));
	this->hints.ai_family = AF_INET;
	this->hints.ai_socktype = SOCK_STREAM;
	this->hints.ai_flags = AI_PASSIVE;
	status = getaddrinfo(NULL, this->portString.c_str(), &this->hints, &this->serverAddr);
	if (status != 0)
	{
		std::cout << "Error getting address info" << std::endl;
		throw(Server::errorException());
	}
	this->serverFd = socket(this->serverAddr->ai_family, this->serverAddr->ai_socktype, this->serverAddr->ai_protocol);
	fcntl(this->serverFd, F_SETFL, O_NONBLOCK);
	if (this->serverFd == -1)
	{
		std::cout << "Error creating socket" << std::endl;
		throw(Server::errorException());
	}
	int	flag = 1;
	if (setsockopt(this->serverFd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) == -1)
	{
		perror("Setsocketopt");
		close(this->serverFd);
		freeaddrinfo(this->serverAddr);
		throw(Server::errorException());
	}
	status	= bind(this->serverFd, this->serverAddr->ai_addr, this->serverAddr->ai_addrlen);
	if (status != 0)
	{
		perror("Error binding socket");
		std::cout << "Binding error details; " << strerror(errno) << std::endl;
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
	int	status;
	status = listen(this->serverFd, BACKLOG);
	if (status != 0)
	{
		perror("Error while listening for connections");
		close(this->serverFd);
		freeaddrinfo(this->serverAddr);
		throw(Server::errorException());
	}
	std::cout << "Server is listening on port " << port << "..." << std::endl;
	freeaddrinfo(this->serverAddr);
}

void	Server::acceptConnection()
{
	struct sockaddr_in	clientAddr = this->clientObj.getClientAddr();
	socklen_t			addrSize = sizeof(this->clientObj.getClientAddr());

	this->clientObj.setClientFd(accept(this->serverFd, (struct sockaddr *)&clientAddr, &addrSize));
	fcntl(this->clientObj.getClientFd(), F_SETFL, O_NONBLOCK);
	if (this->clientObj.getClientFd() == -1)
	{
		perror("Error while accepting connection");
		throw(Server::errorException());
	}
	std::cout << "Connection accepted from " << inet_ntoa(this->clientObj.getClientAddr().sin_addr) << std::endl;
	struct pollfd	poll;
	poll.fd = this->clientObj.getClientFd();
	poll.events = POLLIN;
	poll.revents = 0;
	this->fds.push_back(poll);
}

void	Server::registerUser(std::string buffer, int fd)
{
	try
	{
		std::istringstream	iss(buffer);
		std::string			line;
		while (std::getline(iss, line, '\n'))
		{
			this->parser.push_back(line);
		}
		strVector::iterator	it = parser.begin();
		this->addUser(fd);
		while (it != parser.end())
		{
			if (it->find("CAP") != std::string::npos)
			{
				it++;
				continue ;
			}
			else if (it->find("PASS") != std::string::npos || \
				it->find("NICK") != std::string::npos || it->find("USER") != std::string::npos)
			{
				if (it->find("USER") != std::string::npos)
					std::cout << *it << std::endl;
				std::string	cmd;
				this->usersMap[fd]->parseCommand(*it);
				cmd = this->usersMap[fd]->getCommand()[COMMAND];
				if (!this->commandsMap[cmd])
					throw(Server::errorException());
				this->commandsMap[cmd]->execute(this->usersMap, this->channels, fd);
			}
			else
				throw(Server::errorException());
			this->usersMap[fd]->clearCmdMap();
			it++;
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		send(fd, "HexChat :Registration failed\r\n", 31, 0);
		if (this->usersMap[fd])
		{
			delete this->usersMap[fd];
			this->usersMap.erase(fd);
		}
		this->parser.erase(this->parser.begin(), this->parser.end());
		close (fd);
		return ;
	}
	if (this->usersMap[fd] && this->usersMap[fd]->isAuth())
	{
		std::string	motd = readMotd("./srcs/motd.txt", fd);
		std::string	buffer = RPL_WELCOME(this->usersMap[fd]->getNick(), \
			this->usersMap[fd]->getName(), this->usersMap[fd]->getHost()) + RPL_YOURHOST(this->usersMap[fd]->getNick()) \
			+ RPL_CREATED(this->usersMap[fd]->getNick()) + RPL_MYINFO(this->usersMap[fd]->getNick()) \
			+ RPL_ISUPPORT(this->usersMap[fd]->getNick()) + motd;
		send(fd, buffer.c_str(), buffer.length(), 0);
		this->registeredFds.push_back(fd);
	}
	this->parser.erase(this->parser.begin(), this->parser.end());
}

const std::string	Server::readMotd(const std::string &fn, int fd)
{
	std::fstream	file;
	std::string		buffer;
	std::string		line;

	file.open(fn.c_str(), std::ios::in);
	if (!file.is_open())
		return (ERR_NOMOTD(this->usersMap[fd]->getNick()));
	while (std::getline(file, line))
	{
		buffer += line + "\n";
	}
	file.close();
	buffer = RPL_MOTDSTART(this->usersMap[fd]->getNick()) + RPL_MOTD(usersMap[fd]->getNick(), buffer) \
			+ RPL_ENDOFMOTD(this->usersMap[fd]->getNick());
	return buffer;
}

bool	Server::doesCommandExist(std::string name)
{
	cmdMap::iterator	it = this->commandsMap.find(name);
	if (it != this->commandsMap.end())
		return (true);
	return (false);
}

void	Server::launchCommand(std::map<int, std::string>cmd, int fd)
{
	this->commandsMap[cmd[COMMAND]]->execute(this->usersMap, this->channels, fd);
	if (cmd[COMMAND] == "QUIT")
		this->registeredFds.erase(std::find(this->registeredFds.begin(), this->registeredFds.end(), fd));
}

void	Server::toUpper(std::string &command)
{
	for (size_t i = 0; i < command.length(); i++)
	{
		command[i] = std::toupper(command[i]);
	}
}

void	Server::handleRegisteredCommand(std::string command, int fd)
{
	try
	{
		this->usersMap[fd]->clearCmdMap();
		this->usersMap[fd]->parseCommand(command);
		this->toUpper(this->usersMap[fd]->getCommand()[COMMAND]);
		if(!this->doesCommandExist(this->usersMap[fd]->getCommand()[COMMAND]))
		{
			std::string buffer = ERR_UNKNOWNCOMMAND(this->usersMap[fd]->getNick(), this->usersMap[fd]->getCommand()[COMMAND]);
			send(fd, buffer.c_str(), buffer.length(), 0);
			throw(Command::unknownCommandException());
		}
		this->launchCommand(this->usersMap[fd]->getCommand(), fd);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void	Server::deleteUser(size_t index)
{
	if (this->isRegistered(this->fds[index].fd))
	{
		this->usersMap[this->fds[index].fd]->clearCmdMap();
		this->commandsMap["QUIT"]->execute(this->usersMap, this->channels, this->fds[index].fd);
		if (this->isRegistered(this->fds[index].fd))
			this->registeredFds.erase(std::find(this->registeredFds.begin(), \
			this->registeredFds.end(), this->fds[index].fd));
	}
}

void Server::initServer()
{
	int		bread = 1;
	char	buffer[1024];

	std::memset(&buffer, 0, sizeof(buffer));
	this->createServerSocket();
	this->bindSocket();
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
				{
					this->acceptConnection();
					continue ;
				}
				bread = recv(this->fds[i].fd, buffer, 1000, 0);
				if (bread <= 0)
				{
					this->deleteUser(i);
					continue ;
				}
				if (this->isRegistered(this->fds[i].fd))
					this->handleRegisteredCommand(buffer, this->fds[i].fd);
				else
					this->registerUser(buffer, this->fds[i].fd);
						
				std::memset(&buffer, 0, sizeof(buffer));
			}
		}
	}
	this->closeFds();
}

bool	Server::isRegistered(int fd)
{
	std::vector<int>::iterator	it = std::find(this->registeredFds.begin(), this->registeredFds.end(), fd);
	if (it == this->registeredFds.end())
		return (false);
	return (true);
}

void	Server::addUser(int fd)
{
	if (!this->usersMap[fd])
	{
		User	obj;
		this->usersMap[fd] = obj.clone(this->getPassword());
	}
}

void	Server::closeFds()
{
	std::vector<struct pollfd>::iterator	it = this->fds.begin();
	while (it != this->fds.end())
	{
		close ((*it).fd);
		it++;
	}
}

bool    Server::doesChannelExist(const std::string &name)
{
	if (this->channels.find(name) == this->channels.end())
		return false;
	return true;
}

bool	Server::doesUserExist(const std::string &name)
{
	usrsMap::iterator	it = this->usersMap.begin();
	while (it != this->usersMap.end())
	{
		if ((*it).second->getNick() == name)
			return true;
		it++;
	}
	return false;
}

