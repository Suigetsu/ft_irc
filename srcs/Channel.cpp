/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:54:50 by hrahmane          #+#    #+#             */
/*   Updated: 2024/03/16 13:29:49 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Channel.hpp"

Channel::Channel()
{
    
}

Channel::Channel(const std::string &name) : name(name), userLimit(BACKLOG),  inviteStatus(false), topicStatus(true), limitStatus(false),  keyStatus(false)
{

}

Channel::Channel(const std::string &name, const std::string &password) : name(name), password(password)
{

}

Channel::~Channel()
{
    // std::vector<User *> tmp = this->getUsers();
    // std::vector<User *>::iterator it = tmp.begin();
    // while (it != tmp.end())
    // {
    //     if (*it)
    //         delete *it;
    //     it++;
    //     std::cout << "debug" << std::endl;
    // }
}

const std::string Channel::getName() const
{
    return this->name;
}
const std::vector<User*> &Channel::getUsers() const
{
    return this->users;
}

 const std::string Channel::getPassword() const
 {
    return this->password;
 }
 
void  Channel::addUser(User *user)
{
    if (std::find(users.begin(), users.end(), user) == users.end())
        this->users.push_back(user);
}

void  Channel::removeUser(User *user)
{
    (void)user;
    // std::vector<User*>::iterator it = std::find(users.begin(), users.end(), user);
    // if (it != users.end())
    // {
    //     std::cout << "User : " << user.getNickname() << " has been removed from the channel." << std::endl;
    //     users.erase(it);
    // }
    // else
    //     std::cout << "User : " << user.getNickname() << " is not in the channel." << std::endl;
}

bool    Channel::isOperator(std::string nick) const
{
    if (std::find(this->chanops.begin(), this->chanops.end(), nick) != this->chanops.end())
        return (true);
    return (false);
}

bool  setInviteOnlyMode()
{
    return (true);
}
bool  setTopicRestriction()
{
    return (true);
}
bool  Channel::setChannelKey(std::string key, int fd, std::map<int, User *> &user)
{
    if (!this->getPassword().empty() && key != this->getPassword())
    {
        send (fd, ERR_KEYSET(user[fd]->getNickname(), this->getName()).c_str(), \
        ERR_KEYSET(user[fd]->getNickname(), this->getName()).length(), 0);
        return false;
    }
    this->password = key;
    return true;
}
bool  grantOperatorPriv()
{
    return (true);
}
int  Channel::setUserLimit(int limit)
{
    if (limit <= 0 || limit > this->userLimit)
        return 1;
    this->userLimit = limit;
    return 0;
}

void  Channel::setMode(User *op, const std::string &mode)
{
    (void)op, (void)mode;
    // if (isOperator(op))
    // {
    //     for (int i = 0; i < this->mode.length(); i++)
    //     {
    //         char c = this->mode[i];
    //         switch (c)
    //         {
    //         case 'i':
    //             Channel::setInviteOnlyMode();
    //             break;
    //         case 't':
    //             Channel::setTopicRestriction();
    //             break;
    //         case 'k':
    //             Channel::setChannelKey();
    //             break;
    //         case 'o':
    //             Channel::grantOperatorPriv();
    //             break;
    //         case 'l':
    //             Channel::setUserLimit();
    //             break;
    //         default:
    //             std::cout << mode << ":is unknown mode char to me" << std::endl;
    //             break;
    //         }
    //     }
    // }
}

const std::string Channel::getTopic() const
{
    return (this->topic);
}

bool    Channel::isNameValid(const std::string &name)
{
    if (name.empty() && name.find_first_of("&#+!") == 0)
        return true;
    return false;
}

size_t Channel::getUserLimit()
{
    return (this->userLimit);
}

bool    Channel::getInviteStatus() const
{
    return (this->inviteStatus);
}

bool    Channel::getKeyStatus() const
{
    return (this->keyStatus);
}

bool    Channel::getLimitStatus() const
{
    return (this->limitStatus);
}

bool    Channel::getTopicStatus() const
{
    return (this->topicStatus);
}

void    Channel::setLimitStatus(bool status)
{
    this->limitStatus = status;
}

void    Channel::setKeyStatus(bool status)
{
    this->keyStatus = status;
}

void    Channel::setInviteStatus(bool status)
{
    this->inviteStatus = status;
}

void    Channel::setTopicStatus(bool status)
{
    this->topicStatus = status;
}

void	Channel::joinChannel(std::map<int, User*> users, int fd)
{
    std::cout << this->users.size() + 1 << std::endl;
    std::cout << this->getUserLimit() << std::endl;
    if (this->users.size() + 1 > this->getUserLimit())
    {
        send(fd, ERR_CHANNELISFULL(users[fd]->getNickname(), this->name).c_str(), \
            ERR_CHANNELISFULL(users[fd]->getNickname(), this->name).length(), 0);
        return ;
    }
    if (this->getInviteStatus())
    {
        send(fd, ERR_INVITEONLYCHAN(users[fd]->getNickname(), this->name).c_str(), \
            ERR_INVITEONLYCHAN(users[fd]->getNickname(), this->name).length(), 0);
        return ;
    }
    if (this->getKeyStatus())
    {
        send(fd, ERR_BADCHANNELKEY(users[fd]->getNickname(), this->name).c_str(), \
            ERR_BADCHANNELKEY(users[fd]->getNickname(), this->name).length(), 0);
        return ;
    }
    std::string buffer = JOIN(users[fd]->getNickname(), users[fd]->getUsername(), users[fd]->getHost(), this->name) \
			+ RPL_NAMREPLY(users[fd]->getNickname(), this->getName(), this->bufferizeNames(), \
            this->getPrefix(users[fd]->getNickname())) + RPL_ENDOFNAMES(users[fd]->getNickname(), this->name);
	send(fd, buffer.c_str(), buffer.length(), 0);
    std::vector<User *> tmp = this->getUsers();
    std::vector<User *>::iterator it = tmp.begin();
    while (it != tmp.end())
    {
        send((*it)->getFd(), JOIN(users[fd]->getNickname(), users[fd]->getUsername(), users[fd]->getHost(), this->name).c_str(), \
            JOIN(users[fd]->getNickname(), users[fd]->getUsername(), users[fd]->getHost(), this->name).length(), 0);
        it++;
    }
    this->addUser(users[fd]);
}

const std::string   Channel::bufferizeModes() const
{
    std::string buffer = "+";
    if (this->getKeyStatus())
        buffer += "k";
    if (this->getInviteStatus())
        buffer += "i";
    if (this->getLimitStatus())
        buffer += "l";
    if (this->getTopicStatus())
        buffer += "t";
    return (buffer);
}

const std::string    Channel::bufferizeNames() const
{
    std::string buffer = " ";
    std::vector<User *> tmp = this->getUsers();
    std::vector<User *>::iterator it = tmp.begin();
    while (it != tmp.end())
    {
        buffer += this->getPrefix((*it)->getNickname()) + (*it)->getNickname();
        if (it + 1 != tmp.end())
            buffer += " ";
        it++;
    }
    return (buffer);
}

void	Channel::joinChannel(std::map<int, User*> users, int fd, std::string key)
{
    if (this->users.size() + 1 > this->getUserLimit())
    {
        send(fd, ERR_CHANNELISFULL(users[fd]->getNickname(), this->name).c_str(), \
            ERR_CHANNELISFULL(users[fd]->getNickname(), this->name).length(), 0);
        return ;
    }
    if (this->getInviteStatus())
    {
        send(fd, ERR_INVITEONLYCHAN(users[fd]->getNickname(), this->name).c_str(), \
            ERR_INVITEONLYCHAN(users[fd]->getNickname(), this->name).length(), 0);
        return ;
    }
    if (this->getKeyStatus() && key != this->getPassword())
    {
        send(fd, ERR_BADCHANNELKEY(users[fd]->getNickname(), this->name).c_str(), \
            ERR_BADCHANNELKEY(users[fd]->getNickname(), this->name).length(), 0);
        return ;
    }
    std::string buffer = JOIN(users[fd]->getNickname(), users[fd]->getUsername(), users[fd]->getHost(), this->name) \
			+ RPL_NAMREPLY(users[fd]->getNickname(), this->getName(), \
            this->bufferizeNames(), this->getPrefix(users[fd]->getNickname())) \
            + RPL_ENDOFNAMES(users[fd]->getNickname(), this->name);
	send(fd, buffer.c_str(), buffer.length(), 0);
    this->broadcastToMembers(JOIN(users[fd]->getNickname(), users[fd]->getUsername(), users[fd]->getHost(), this->name));
    this->addUser(users[fd]);
}

void    Channel::broadcastToMembers(std::string message)
{
    std::vector<User *> tmp = this->getUsers();
    std::vector<User *>::iterator it = tmp.begin();
    while (it != tmp.end())
    {
        send((*it)->getFd(), message.c_str(), message.length(), 0);
        it++;
    }
}

void	Channel::leaveChannel(User *user, const std::string &name)
{
    (void)user, (void)name;
}

Channel *Channel::clone(const std::string &name) const
{
    return (new Channel(name));
}

void    Channel::unsetOperator(User *user)
{
    std::vector<std::string>::iterator it = std::find(this->chanops.begin(), this->chanops.end(), user->getNickname());
    if (it != this->chanops.end())
        this->chanops.erase(it);
}

std::string   Channel::getPrefix(std::string nick) const
{
    if (this->isOperator(nick) == true)
        return ("@");
    return ("");
}

void    Channel::setOperator(User *user)
{
    if (this->isOperator(user->getNickname()) == false)
        this->chanops.push_back(user->getNickname());
}

User *Channel::getUser(std::string nickname) const
{
    std::vector<User *>::iterator it = const_cast<std::vector<User *> &>(this->getUsers()).begin();
    while (it != const_cast<std::vector<User *> &>(this->getUsers()).end())
    {
        if ((*it)->getNickname() == nickname)
            return (*it);
        it++;
    }
    return NULL;
}

void    Channel::setTopic(std::string topic)
{
    this->topic = topic;
}

bool    Channel::isWithinChannel(std::string nickname) const
{
    if (this->getUser(nickname) == NULL)
        return false;
    return true;
}

void    Channel::unsetChannelKey()
{
    this->password.clear();
}

void    Channel::removePassword(std::string arg, std::map<int, User *> &user, int fd)
{
    if (arg != this->getPassword())
    {
        send (fd, ERR_KEYSET(user[fd]->getNickname(), this->getName()).c_str(), \
        ERR_KEYSET(user[fd]->getNickname(), this->getName()).length(), 0);
        return ;
    }
    this->unsetChannelKey();
    this->setKeyStatus(false);
}

void    Channel::createChannel(std::map<int, User*> users, int fd)
{
    this->addUser(users[fd]);
    this->setOperator(users[fd]);
    std::string buffer = JOIN(users[fd]->getNickname(), users[fd]->getUsername(), users[fd]->getHost(), this->getName()) \
			+ RPL_NAMREPLY(users[fd]->getNickname(), this->getName(), "", this->getPrefix(users[fd]->getNickname())) + \
            RPL_ENDOFNAMES(users[fd]->getNickname(), this->name);
	send(fd, buffer.c_str(), buffer.length(), 0);
}
