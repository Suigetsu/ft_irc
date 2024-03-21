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
		strVector				modes;
		strVector				args;
		std::stack<std::string>	parseStack;
		std::string				setBuffer;
		std::string				setArgs;
		std::string				unsetBuffer;
	public:
		Mode();
		~Mode();
		void				execute(usrsMap &users, chanMap &chan, int fd) const;
		Mode				*clone() const;
		void    			parseModes(usrsMap &users, std::string params, chanMap &chan, int fd) const;
		void				bufferizeModes(char mode, char sign) const;
		void    			setMode(char mode, std::string arg, usrsMap &user, Channel **chan, int fd) const;
		void				setMode(char mode, usrsMap &user, Channel **chan, int fd) const;
		void				unsetMode(char mode, std::string arg, usrsMap &user, Channel **chan, int fd) const;
		void				unsetMode(char mode, usrsMap &user, Channel **chan, int fd) const;
		void				bufferizeModes(char mode, char sign, std::string args) const;
		bool				doesChanExist(chanMap &chan, std::string name) const;
		int					doesUserExist(usrsMap &usrs, std::string nick) const;
		void				clearBuffers() const;
		int 				setOMode(usrsMap &users, std::string mode, Channel **chan, int fd) const;
		const std::string	getModeBuffer() const;

};