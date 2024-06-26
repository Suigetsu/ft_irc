#include "../includes/Mode.hpp"

Mode::Mode() : Command::Command()
{
	
}

Mode::~Mode()
{

}


int	Mode::doesUserExist(usrsMap &usrs, std::string nick) const
{
	usrsMap::iterator it = usrs.begin();
	while (it != usrs.end())
	{
		if (it->second->getNick() == nick)
			return it->second->getFd();
		it++;
	}
	return -1;
}

bool	Mode::doesChanExist(chanMap &chan, std::string name) const
{
	chanMap::iterator it = chan.begin();
	while (it != chan.end())
	{
		if (it->second->getName() == name)
			return true;
		it++;
	}
	return false;
}

void	Mode::unsetMode(char mode, std::string arg, usrsMap &user, Channel **chan, int fd) const
{
    switch (mode)
    {
        case 'k':
        {
            if ((*chan)->removePassword(arg, user, fd) == 1)
                return ;
            break;
        }
        case 'o':
        {
            if (this->doesUserExist(user, arg) == -1)
            {
                send (fd, ERR_NOSUCHNICK(user[fd]->getNick(), arg).c_str(), \
                    ERR_NOSUCHNICK(user[fd]->getNick(), arg).length(), 0);
                return ;
            }
            if ((*chan)->isWithinChannel(arg) == false)
            {
                send (fd, ERR_USERNOTINCHANNEL(user[fd]->getNick(), arg, (*chan)->getName()).c_str(), \
                    ERR_USERNOTINCHANNEL(user[fd]->getNick(), arg, (*chan)->getName()).length(), 0);
                return ;
            }
            (*chan)->unsetOperator((*chan)->getUser(arg));
            break;
        }
        default:
            send (fd, ERR_UNKNOWNMODE(user[fd]->getNick(), mode).c_str(), \
                ERR_UNKNOWNMODE(user[fd]->getNick(), mode).length(), 0);
            break;
    }
    this->bufferizeModes(mode, '-', arg);
}

void	Mode::unsetMode(char mode, usrsMap &user, Channel **chan, int fd) const
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
            send (fd, ERR_UNKNOWNMODE(user[fd]->getNick(), mode).c_str(), \
                ERR_UNKNOWNMODE(user[fd]->getNick(), mode).length(), 0);
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

void    Mode::setMode(char mode, usrsMap &user, Channel **chan, int fd) const
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
            send (fd, ERR_UNKNOWNMODE(user[fd]->getNick(), mode).c_str(), \
                ERR_UNKNOWNMODE(user[fd]->getNick(), mode).length(), 0);
            return ;
    }
    this->bufferizeModes(mode, '+');
}

int Mode::setOMode(usrsMap &users, std::string arg, Channel **chan, int fd) const
{
    if (this->doesUserExist(users, arg) == -1)
    {
        send (fd, ERR_NOSUCHNICK(users[fd]->getNick(), arg).c_str(), \
                ERR_NOSUCHNICK(users[fd]->getNick(), arg).length(), 0);
        return 1;
    }
    if ((*chan)->isWithinChannel(arg) == false)
    {
        send (fd, ERR_USERNOTINCHANNEL(users[fd]->getNick(), arg, (*chan)->getName()).c_str(), \
            ERR_USERNOTINCHANNEL(users[fd]->getNick(), arg, (*chan)->getName()).length(), 0);
        return 1;
    }
    return 0;
}

void    Mode::setMode(char mode, std::string arg, usrsMap &user, Channel **chan, int fd) const
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
            if (this->setOMode(user, arg, chan, fd) == 1)
                return ;
            (*chan)->setOperator((*chan)->getUser(arg));
            break;
        }
        default:
        {
            send (fd, ERR_UNKNOWNMODE(user[fd]->getNick(), mode).c_str(), \
                ERR_UNKNOWNMODE(user[fd]->getNick(), mode).length(), 0);
            return ;
        }
    }
    this->bufferizeModes(mode, '+', arg);
}

void    Mode::parseModes(usrsMap &user, std::string params, chanMap &chan, int fd) const
{
    std::map<std::string, std::string> modeMap;
    strVector modeargs;
    std::istringstream iss(params);
    std::string token;
    std::string sign;
    while (std::getline(iss, token, ' '))
    {
        modeargs.push_back(token);
    }
    if (this->doesChanExist(chan, modeargs[0]) == false)
    {
        send(fd, ERR_NOSUCHCHANNEL(user[fd]->getNick(), modeargs[0]).c_str(), \
            ERR_NOSUCHCHANNEL(user[fd]->getNick(), modeargs[0]).length(), 0);
        return ;
    }
    if (!chan[modeargs[0]]->isWithinChannel(user[fd]->getNick()))
    {
        send (fd, ERR_NOTONCHANNEL(user[fd]->getNick(), modeargs[0]).c_str(), \
            ERR_NOTONCHANNEL(user[fd]->getNick(), modeargs[0]).length(), 0);
        return ;
    }
    if (modeargs.size() < 2)
    {
        send(fd, RPL_CHANNELMODEIS(user[fd]->getNick(), modeargs[0], chan[modeargs[0]]->bufferizeModes()).c_str(), \
            RPL_CHANNELMODEIS(user[fd]->getNick(), modeargs[0], chan[modeargs[0]]->bufferizeModes()).length(), 0);
        return ;
    }
    if (chan[modeargs[0]]->isOperator(user[fd]->getNick()) == false)
    {
        send(fd, ERR_CHANOPRIVSNEEDED(user[fd]->getNick(), modeargs[0]).c_str(), \
            ERR_CHANOPRIVSNEEDED(user[fd]->getNick(), modeargs[0]).length(), 0);
        return ;
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
                    send (fd, ERR_NEEDMOREPARAMS(user[fd]->getNick(), modeargs[i][j]).c_str(), \
                        ERR_NEEDMOREPARAMS(user[fd]->getNick(), modeargs[i][j]).length(), 0);
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
                            send (fd, ERR_NEEDMOREPARAMS(user[fd]->getNick(), modeargs[i][j]).c_str(), \
                                ERR_NEEDMOREPARAMS(user[fd]->getNick(), modeargs[i][j]).length(), 0);
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
        chan[modeargs[0]]->broadcastToMembers(MODE(user[fd]->getNick(), user[fd]->getName(), user[fd]->getHost(), \
            chan[modeargs[0]]->getName(), this->getModeBuffer()));
        this->clearBuffers();
    }
}

void    Mode::clearBuffers() const
{
    const_cast<std::string &>(this->setBuffer).clear();
    const_cast<std::string &>(this->unsetBuffer).clear();
    const_cast<std::string &>(this->setArgs).clear();
}

void	Mode::execute(usrsMap &users, chanMap &chan, int fd) const
{
    if (users[fd]->getCommand().size() < 2)
    {
        send(fd, ERR_NEEDMOREPARAMS(users[fd]->getNick(), users[fd]->getCommand()[COMMAND]).c_str(), \
            ERR_NEEDMOREPARAMS(users[fd]->getNick(), users[fd]->getCommand()[COMMAND]).length(), 0);
        return ;
    }
	this->parseModes(users, users[fd]->getCommand()[FIRST_PARAM], chan, fd);
}


Mode	*Mode::clone() const
{
	return (new Mode);
}