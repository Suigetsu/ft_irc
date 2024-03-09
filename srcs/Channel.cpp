/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:54:50 by hrahmane          #+#    #+#             */
/*   Updated: 2024/03/09 16:16:07 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Channel.hpp"

Channel::Channel()
{
    
}

Channel::Channel(const std::string &name) : name(name), userLimit(BACKLOG),  inviteStatus(false), topicStatus(false), limitStatus(false),  keyStatus(false)
{

}

Channel::Channel(const std::string &name, const std::string &password) : name(name), password(password)
{

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
    (void)user;
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

bool    Channel::isOperator(User *user) const
{
    (void)user;
    return (true);
    // return std::find(chanops.begin(), chanops.end(), user) != chanops.end();
}

bool  setInviteOnlyMode()
{
    return (true);
}
bool  setTopicRestriction()
{
    return (true);
}
bool  setChannelKey()
{
    return (true);
}
bool  grantOperatorPriv()
{
    return (true);
}
void  Channel::setUserLimit(int limit)
{
    if (limit <= 0 || limit > this->userLimit)
        return ;
    this->userLimit = limit;
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

bool    Channel::getInviteStatus()
{
    return (this->inviteStatus);
}

bool    Channel::getKeyStatus()
{
    return (this->keyStatus);
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
			+ RPL_NAMREPLY(users[fd]->getNickname(), users[fd]->getUsername(), this->getName(), users[fd]->getHost(), \
            this->bufferizeNames(), users[fd]->getPrefix()) \
            + RPL_ENDOFNAMES(users[fd]->getUsername(), this->name);
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
    std::cout << buffer << std::endl;
}


const std::string    Channel::bufferizeNames() const
{
    std::string buffer = " ";
    std::vector<User *> tmp = this->getUsers();
    std::vector<User *>::iterator it = tmp.begin();
    while (it != tmp.end())
    {
        buffer += (*it)->getPrefix() + (*it)->getNickname() + "!" + (*it)->getUsername() + "@" + (*it)->getHost();
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
    std::cout << "debug" << std::endl;
    this->addUser(users[fd]);
    std::string buff = ":localhost 353 " + users[fd]->getNickname() + " = " + this->name + " :" + users[fd]->getNickname() \
        + "!" + users[fd]->getUsername() + "@" + users[fd]->getHost() + " " +  "@" + this->getUsers()[0]->getNickname() + "!" \
        + this->getUsers()[0]->getUsername() + "@" + this->getUsers()[0]->getHost() + "\r\n";
    std::string buffer = JOIN(users[fd]->getNickname(), users[fd]->getUsername(), users[fd]->getHost(), this->name) \
			+ buff;
	send(fd, buffer.c_str(), buffer.length(), 0);
    std::cout << buffer << std::endl;
    // if ()
	// (void) user, (void) name;
	// if (!name.empty() && name.find_first_of("&#+!") == 0)
	// {
	// 	if (name.length() <= 50)
	// 	{
	// 		if (this->channels.find(name) == this->channels.end())
	// 		{
	// 			this->channels[name] = new Channel(name, "");
	// 			std::cout << "Channel " << name << " has been created." << std::endl;
	// 		}
	// 		else
	// 			std::cout << "Channel " << name << "already exists." << std::endl;
	// 		if (this->channels[name]->getUsers().empty())
	// 		{
	// 			this->channels[name]->addUser(user);
	// 			std::cout << "User " << user.getNickname() << " is the operator of channel " << name << std::endl;
	// 		}
	// 		if (this->channels[name]->setInviteOnlyMode() && !this->channels[name]->isOperator(user))
	// 		{
	// 			std::cout << "User " << user.getNickname() << ":Cannot join channel (+i)" << std::endl;
	// 			return ;
	// 		}
	// 		if (std::find(this->channels[name]->getUsers().begin(), this->channels[name]->getUsers().end(), user) == this->channels[name]->getUsers().end())
	// 		{
	// 			this->channels[name]->addUser(user);
	// 			std::cout << "User " << user.getNickname() << " has joined the channel " << name << std::endl;
	// 		}
	// 	}
	// 	else
	// 		std::cout << "Channel name should not exceed 50 chars." << std::endl;
	// }
	// else
	// 	std::cout << "Invalid channel name." << std::endl;
}

void	Channel::leaveChannel(User *user, const std::string &name)
{
    (void)user, (void)name;
	// (void) id, (void) name;
	// std::vector<User*>::iterator userIt = std::find(this->users.begin(), this->users.end(), user);
    // if (userIt != this->users.end())
    //     this->users.erase(userIt);
}

Channel *Channel::clone(const std::string &name) const
{
    return (new Channel(name));
}

void    Channel::setOperator(User *user)
{
    std::vector<std::string>::iterator it = std::find(this->chanops.begin(), this->chanops.end(), user->getNickname());
    if (it != this->chanops.end())
        this->chanops.push_back(user->getNickname());
    user->setPrefix("@");
}

void    Channel::createChannel(std::map<int, User*> users, int fd)
{
    this->addUser(users[fd]);
    this->setOperator(users[fd]);
    std::string buffer = JOIN(users[fd]->getNickname(), users[fd]->getUsername(), users[fd]->getHost(), this->getName()) \
			+ RPL_NAMREPLY(users[fd]->getNickname(), users[fd]->getUsername(), this->getName(), users[fd]->getHost(), "", users[fd]->getPrefix()) + \
            RPL_ENDOFNAMES(users[fd]->getUsername(), this->name);
	send(fd, buffer.c_str(), buffer.length(), 0);
}
