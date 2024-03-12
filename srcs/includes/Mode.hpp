/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:00:16 by hrahmane          #+#    #+#             */
/*   Updated: 2024/03/11 16:39:35 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "User.hpp"
#include "Command.hpp"
#include "Channel.hpp"
#include <string>
#include <iostream>
#include <stack>

class Command;

class	Mode : public Command
{
	private:
		std::vector<std::string> modes;
		std::vector<std::string> args;
		std::stack<std::string> parseStack;
		std::string setBuffer;
		std::string setArgs;
		std::string unsetBuffer;
	public:
		Mode();
		~Mode();
		void	execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const;
		Mode	*clone() const;
		void    parseModes(std::map<int, User *> &users, std::string params, std::map<std::string, Channel *> &chan, int fd) const;
		void	bufferizeModes(char mode, char sign) const;
		void    setMode(char mode, std::string arg, std::map<int, User *> &user, Channel **chan, int fd) const;
		void	setMode(char mode, std::map<int, User *> &user, Channel **chan, int fd) const;
		void	unsetMode(char mode, std::string arg, std::map<int, User *> &user, Channel **chan, int fd) const;
		void	unsetMode(char mode, std::map<int, User *> &user, Channel **chan, int fd) const;
		void	bufferizeModes(char mode, char sign, std::string args) const;
		void	clearBuffers() const;
		const std::string getModeBuffer() const;

};