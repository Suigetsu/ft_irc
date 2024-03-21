#ifndef USER_HPP
#define USER_HPP

#include "Client.hpp"
#include <string>
#include <sstream>

# define COMMAND 0
# define FIRST_PARAM 1
# define SECOND_PARAM 2
# define THIRD_PARAM 3

class User {
private:
	std::string nickname;
	std::string username;
	std::string serverPass;
	std::string userPass;
	std::string host;
	std::string realname;
	std::string prefix;
	int fd;
	std::map<int, std::string> cmd;
	bool auth;

public:
	User();
	User(std::string pass);
	~User();
	User *clone(std::string pass) const;
	void setFd(int fd);
	void setNickname(const std::string &name);
	void setUsername(const std::string &name);
	void setUserPass(const std::string &pass);
	void setHost(const std::string &host);
	void setRealname(const std::string &name);
	void setPrefix(const std::string &prefix);
	void setAuth(bool auth);
	int getFd();
	const std::string &getNick() const;
	const std::string &getName() const;
	const std::string &getUserPass() const;
	const std::string &getServerPass() const;
	const std::string &getHost() const;
	const std::string &getRealname() const;
	const std::string &getPrefix() const;
	bool isAuth();
	void	parseCommand(std::string command);
	void	clearCmdMap();
	std::map<int, std::string> &getCommand();
};

#endif
