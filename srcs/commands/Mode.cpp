/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:03:01 by hrahmane          #+#    #+#             */
/*   Updated: 2024/03/14 12:07:39 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Mode.hpp"

Mode::Mode() : Command::Command()
{
	
}

Mode::~Mode()
{

}


void	Mode::unsetMode(char mode, std::string arg, std::map<int, User *> &user, Channel **chan, int fd) const
{
    switch (mode)
    {
        case 'k':
            (*chan)->removePassword(arg, user, fd);
            break;
        case 'o':
        {
            if ((*chan)->isWithinChannel(arg) == false)
            {
                send (fd, ERR_NOSUCHNICK(user[fd]->getNickname(), arg).c_str(), \
                    ERR_NOSUCHNICK(user[fd]->getNickname(), arg).length(), 0);
                return ;
            }
            (*chan)->unsetOperator((*chan)->getUser(arg));
            break;
        }
        default:
            send (fd, ERR_UNKNOWNMODE(user[fd]->getNickname(), mode).c_str(), \
                ERR_UNKNOWNMODE(user[fd]->getNickname(), mode).length(), 0);
            break;
    }
    this->bufferizeModes(mode, '-', arg);
}

void	Mode::unsetMode(char mode, std::map<int, User *> &user, Channel **chan, int fd) const
{
    switch (mode)
    {
        case 'i':
            (*chan)->setInviteStatus(false);
            break ;
        case 't':
            (*chan)->setTopicStatus(false);
            break ;
        case 'l':
            (*chan)->setLimitStatus(false);
            (*chan)->setUserLimit(BACKLOG);
            break ;
        default:
            send (fd, ERR_UNKNOWNMODE(user[fd]->getNickname(), mode).c_str(), \
                ERR_UNKNOWNMODE(user[fd]->getNickname(), mode).length(), 0);
            return ;
    }
    this->bufferizeModes(mode, '-');
}

const std::string Mode::getModeBuffer() const
{
    return (this->setBuffer + this->unsetBuffer + " " + this->setArgs);
}

void Mode::bufferizeModes(char mode, char sign, std::string args) const
{
    if (sign == '+')
    {
        if (this->setBuffer.empty())
            const_cast<std::string&>(this->setBuffer) = '+';
        if (this->setBuffer.find(mode) == std::string::npos)
        {
            const_cast<std::string&>(this->setBuffer) += mode;
            const_cast<std::string&>(this->setArgs) += args;
            const_cast<std::string&>(this->setArgs) += " ";
        }
    }
    else
    {
        if (this->unsetBuffer.empty())
            const_cast<std::string&>(this->unsetBuffer) = '-';
        if (this->unsetBuffer.find(mode) == std::string::npos)
        {
            const_cast<std::string&>(this->unsetBuffer) += mode;
            const_cast<std::string&>(this->setArgs) += args;
            const_cast<std::string&>(this->setArgs) += " ";
        }
    }
}

void Mode::bufferizeModes(char mode, char sign) const
{
    if (sign == '+')
    {
        if (this->setBuffer.empty())
            const_cast<std::string&>(this->setBuffer) = '+';
        if (this->setBuffer.find(mode) == std::string::npos)
            const_cast<std::string&>(this->setBuffer) += mode;
    }
    else
    {
        if (this->unsetBuffer.empty())
            const_cast<std::string&>(this->unsetBuffer) = '-';
        if (this->unsetBuffer.find(mode) == std::string::npos)
            const_cast<std::string&>(this->unsetBuffer) += mode;
    }
}

void    Mode::setMode(char mode, std::map<int, User *> &user, Channel **chan, int fd) const
{
    switch (mode)
    {
        case 'i':
            (*chan)->setInviteStatus(true);
            break ;
        case 't':
            (*chan)->setTopicStatus(true);
            break ;
        default:
            send (fd, ERR_UNKNOWNMODE(user[fd]->getNickname(), mode).c_str(), \
                ERR_UNKNOWNMODE(user[fd]->getNickname(), mode).length(), 0);
            return ;
    }
    this->bufferizeModes(mode, '+');
}

void    Mode::setMode(char mode, std::string arg, std::map<int, User *> &user, Channel **chan, int fd) const
{
    switch (mode)
    {
        case 'l':
        {
            char *pEnd = NULL;
            errno = 0;
            const long i = std::strtol(arg.c_str(), &pEnd, 10);
            if (errno == ERANGE || errno == EINVAL || *pEnd)
                return ;
            if ((*chan)->setUserLimit(i) == 1)
                return ;
            (*chan)->setLimitStatus(true);
            break;
        }
        case 'k':
        {
            if ((*chan)->setChannelKey(arg, fd, user) == false)
                return ;
            (*chan)->setKeyStatus(true);
            break;
        }
        case 'o':
        {
            if ((*chan)->isWithinChannel(arg) == false)
            {
                send (fd, ERR_NOSUCHNICK(user[fd]->getNickname(), arg).c_str(), \
                    ERR_NOSUCHNICK(user[fd]->getNickname(), arg).length(), 0);
                return ;
            }
            (*chan)->setOperator((*chan)->getUser(arg));
            break;
        }
        default:
        {
            send (fd, ERR_UNKNOWNMODE(user[fd]->getNickname(), mode).c_str(), \
                ERR_UNKNOWNMODE(user[fd]->getNickname(), mode).length(), 0);
            return ;
        }
    }
    this->bufferizeModes(mode, '+', arg);
}

void    Mode::parseModes(std::map<int, User *> &user, std::string params, std::map<std::string, Channel *> &chan, int fd) const
{
    std::map<std::string, std::string> modeMap;
    std::vector<std::string> modeargs;
    std::istringstream iss(params);
    std::string token;
    std::string sign;
    while (std::getline(iss, token, ' '))
    {
        modeargs.push_back(token);
    }
    if (!chan[modeargs[0]])
    {
        send(fd, ERR_NOSUCHCHANNEL(user[fd]->getNickname(), modeargs[0]).c_str(), \
            ERR_NOSUCHCHANNEL(user[fd]->getNickname(), modeargs[0]).length(), 0);
        throw (Mode::unknownCommandException());
    }
    if (modeargs.size() < 2)
    {
        send(fd, RPL_CHANNELMODEIS(user[fd]->getNickname(), modeargs[0], chan[modeargs[0]]->bufferizeModes()).c_str(), \
            RPL_CHANNELMODEIS(user[fd]->getNickname(), modeargs[0], chan[modeargs[0]]->bufferizeModes()).length(), 0);
        throw (Mode::unknownCommandException());
    }
    if (chan[modeargs[0]]->isOperator(user[fd]->getNickname()) == false)
    {
        send(fd, ERR_CHANOPRIVSNEEDED(user[fd]->getNickname(), modeargs[0]).c_str(), \
            ERR_CHANOPRIVSNEEDED(user[fd]->getNickname(), modeargs[0]).length(), 0);
        throw (Mode::unknownCommandException());
    }
    size_t i = 1;
    size_t helper = 1;
    while (i < modeargs.size())
    {
        size_t j = 0;
        while (j < modeargs[i].length())
        {
            while (modeargs[i][j] == '+' || modeargs[i][j] == '-')
            {
                sign = modeargs[i][j];
                j++;
            }
            if (j < modeargs[i].length() && (modeargs[i][j] == 'o' || modeargs[i][j] == 'k'))
            {
                if (i + helper < modeargs.size())
                {
                    if (sign == "+")
                        setMode(modeargs[i][j], modeargs[i + helper], user, &chan[modeargs[0]], fd);
                    else if (sign == "-")
                        unsetMode(modeargs[i][j], modeargs[i + helper], user, &chan[modeargs[0]], fd);
                    modeargs.erase(modeargs.begin() + i + helper);
                }
                else
                    send (fd, ERR_NEEDMOREPARAMS(user[fd]->getNickname(), modeargs[i][j]).c_str(), \
                        ERR_NEEDMOREPARAMS(user[fd]->getNickname(), modeargs[i][j]).length(), 0);
            }
            else if (j < modeargs[i].length() && modeargs[i][j] != 'o' && modeargs[i][j] != 'k')
            {
                if (sign == "+")
                {
                    if (modeargs[i][j] == 'l')
                    {
                        if (i + helper < modeargs.size())
                        {
                            setMode(modeargs[i][j], modeargs[i + helper], user, &chan[modeargs[0]], fd);
                            modeargs.erase(modeargs.begin() + i + helper);
                        }
                        else
                            send (fd, ERR_NEEDMOREPARAMS(user[fd]->getNickname(), modeargs[i][j]).c_str(), \
                                ERR_NEEDMOREPARAMS(user[fd]->getNickname(), modeargs[i][j]).length(), 0);
                    }
                    else
                        setMode(modeargs[i][j], user, &chan[modeargs[0]], fd);
                }
                else if (sign == "-")
                    unsetMode(modeargs[i][j], user, &chan[modeargs[0]], fd);
            }
            j++;
        }
        i++;
    }
    if (!this->getModeBuffer().empty())
    {
        send (fd, MODE(user[fd]->getNickname(), user[fd]->getUsername(), user[fd]->getHost(), chan[modeargs[0]]->getName(), this->getModeBuffer()).c_str(), \
        MODE(user[fd]->getNickname(), user[fd]->getUsername(), user[fd]->getHost(), chan[modeargs[0]]->getName(), this->getModeBuffer()).length(), 0);
        this->clearBuffers();
    }
}

void    Mode::clearBuffers() const
{
    const_cast<std::string &>(this->setBuffer).clear();
    const_cast<std::string &>(this->unsetBuffer).clear();
    const_cast<std::string &>(this->setArgs).clear();
}

void	Mode::execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const
{
    if (users[fd]->getCommand().size() < 2)
    {
        send(fd, ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).c_str(), \
            ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).length(), 0);
        throw (Mode::unknownCommandException());
    }
	this->parseModes(users, users[fd]->getCommand()[FIRST_PARAM], chan, fd);
}


Mode	*Mode::clone() const
{
	return (new Mode);
}