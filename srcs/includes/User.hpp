/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:36:18 by mlagrini          #+#    #+#             */
/*   Updated: 2024/03/07 09:17:10 by hrahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	std::string nicknameHelper;
	std::map<int, std::string> cmd;
	bool auth;

public:
	User();
	User(std::string pass);
	~User();
	User *clone(std::string pass) const;
	void setNickname(const std::string &name);
	void setUsername(const std::string &name);
	void setUserPass(const std::string &pass);
	void setHost(const std::string &host);
	void setRealname(const std::string &name);
	void setNickHelper(const std::string &name);
	void setAuth(bool auth);
	const std::string &getNickname() const;
	const std::string &getUsername() const;
	const std::string &getUserPass() const;
	const std::string &getServerPass() const;
	const std::string &getHost() const;
	const std::string &getRealname() const;
	const std::string &getNickHelper() const;
	bool isAuth();
	void	parseCommand(std::string command);
	std::map<int, std::string> &getCommand();
};

#endif
