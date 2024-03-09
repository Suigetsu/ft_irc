/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:03:01 by hrahmane          #+#    #+#             */
/*   Updated: 2024/03/09 19:37:55 by hrahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Mode.hpp"

Mode::Mode() : Command::Command()
{
	
}

Mode::~Mode()
{

}

void    parseModes(std::string user, std::string params, std::map<std::string, Channel *> &chan, int fd)
{
    std::vector<std::string> modeargs;
    std::istringstream iss(params);
    std::string token;
    while (std::getline(iss, token, ' '))
    {
        modeargs.push_back(token);
    }
    if (!chan[modeargs[0]])
    {
        send(fd, ERR_NOSUCHCHANNEL(user, modeargs[0]).c_str(), ERR_NOSUCHCHANNEL(user, modeargs[0]).length(), 0);
        throw(Mode::unknownCommandException());
    }
    else if (modeargs.size() < 2)
    {
        send(fd, RPL_CHANNELMODEIS(user, modeargs[0], chan[modeargs[0]]->bufferizeModes()).c_str(), \
            RPL_CHANNELMODEIS(user, modeargs[0], chan[modeargs[0]]->bufferizeModes()).length(), 0);
        throw(Mode::unknownCommandException());
    }
}

void	Mode::execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const
{
    
	
}


Mode	*Mode::clone() const
{
	return (new Mode);
}