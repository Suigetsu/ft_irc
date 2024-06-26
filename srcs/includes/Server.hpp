#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <cstring>
# include <string>
# include <sstream>
# include <fstream>
# include <cerrno>
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
# include "UserCmd.hpp"
# include "Quit.hpp"
# include "Ping.hpp"
# include "Channel.hpp"
# include "Join.hpp"
# include "Mode.hpp"
# include "Topic.hpp"
# include "Who.hpp"
# include "WhoIs.hpp"
# include "Motd.hpp"
# include "Privmsg.hpp"
# include "Notice.hpp"
# include "Invite.hpp"
# include "Part.hpp"
# include "Kick.hpp"
# include <poll.h>
# include <fstream>

# define BACKLOG 10
# define COMMAND 0
# define FIRST_PARAM 1
# define SECOND_PARAM 2
# define THIRD_PARAM 3

typedef std::map<int, User *> usrsMap;
typedef std::map<std::string, Channel *> chanMap;
typedef std::map<std::string, Command *> cmdMap;
typedef std::vector<std::string> strVector;

class	Server
{
	private:
		int	port;
		std::string portString;
		std::string password;
		struct addrinfo hints;
		struct addrinfo *serverAddr;
		int	serverFd;
		Client clientObj;
		strVector parser;
		usrsMap usersMap;
		chanMap channels;
		cmdMap commandsMap;
		std::vector<struct pollfd> fds;
		std::vector<int> registeredFds;
	public:
		static bool 		status;
		static bool 		QuitStatus;
		Server();
		~Server();
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
			map.erase(map.begin(), map.end());
		}
		long				getPort() const;
		std::string			getPassword() const;
		void				initServer();
		void				createServerSocket();
		static void 		signalHandler(int signum);
		void				checkParameters(char **args);
		void				bindSocket();
		void				acceptConnection();
		void				registerUser(std::string buffer, int clientFd);
		bool				isRegistered(int fd);
		void				addUser(int fd);
		void				closeFds();
		bool    			doesChannelExist(const std::string &name);
		bool				doesUserExist(const std::string &name);
		void				handleRegisteredCommand(std::string command, int fd);
		bool				doesCommandExist(std::string cmdName);
		void				launchCommand(std::map<int, std::string>cmd, int fd);
		const std::string	readMotd(const std::string &file, int fd);
		void				toUpper(std::string &command);
		void				deleteUser(size_t index);
		
};

#endif
