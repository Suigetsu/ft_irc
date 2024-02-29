/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:36:18 by mlagrini          #+#    #+#             */
/*   Updated: 2024/02/29 18:31:57 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
#define USER_HPP

#include "Client.hpp"
#include <string>

class User {
private:
	std::string nickname;
	std::string username;
	std::string serverPass;
	std::string userPass;
	std::string host;
	std::string realname;
	std::string nicknameHelper;
	bool auth;

public:
	User();
	User(std::string pass);
	~User();
	User *clone(std::string pass) const;
	void setNickname(std::string name);
	void setUsername(std::string name);
	void setUserPass(std::string pass);
	void setHost(std::string host);
	void setRealname(std::string name);
	void setNickHelper(std::string name);
	void setAuth(bool auth);
	std::string getNickname();
	std::string getUsername();
	std::string getUserPass();
	std::string	getServerPass();
	std::string getHost();
	std::string getRealname();
	std::string	getNickHelper();
	bool isAuth();
};

#endif
