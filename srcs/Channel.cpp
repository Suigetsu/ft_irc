/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:54:50 by hrahmane          #+#    #+#             */
/*   Updated: 2024/03/04 15:49:19 by hrahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Channel.hpp"

Channel::Channel()
{
    
}

Channel::Channel(const std::string &name, const std::string &password) : name(name), password(password)
{

}

const std::string Channel::getName() const
{
    return this->name;
}
const std::vector<User> &Channel::getUsers() const
{
    return this->users;
}

 const std::string Channel::getPassword() const
 {
    return this->password;
 }
 
void  Channel::addUser(User user)
{
    if (std::find(users.begin(), users.end(), user) == users.end())
        this->users.push_back(user);
    std::cout << "User is already in the channel." << std::endl;
}

void  Channel::removeUser(User user)
{
    std::vector<User>::iterator it = std::find(users.begin(), users.end(), user);
    if (it != users.end())
    {
        std::cout << "User : " << user.getNickname() << " has been removed from the channel." << std::endl;
        users.erase(it);
    }
    else
        std::cout << "User : " << user.getNickname() << " is not in the channel." << std::endl;
}

bool    Channel::isOperator(User user) const
{
    return std::find(chanops.begin(), chanops.end(), user) != chanops.end();
}

bool  setInviteOnlyMode()
{
    
}
bool  setTopicRestriction()
{
    
}
bool  setChannelKey()
{
    
}
bool  grantOperatorPriv()
{
    
}
bool  setUserLimit()
{
    
}

void  Channel::setMode(User op, const std::string &mode)
{
    if (isOperator(op))
    {
        for (int i = 0; i < this->mode.length(); i++)
        {
            char c = this->mode[i];
            switch (c)
            {
            case 'i':
                Channel::setInviteOnlyMode();
                break;
            case 't':
                Channel::setTopicRestriction();
                break;
            case 'k':
                Channel::setChannelKey();
                break;
            case 'o':
                Channel::grantOperatorPriv();
                break;
            case 'l':
                Channel::setUserLimit();
                break;
            default:
                std::cout << mode << ":is unknown mode char to me" << std::endl;
                break;
            }
        }
    }
}

void	Channel::joinChannel(User user, const std::string &name)
{
	// (void) user, (void) name;
	if (!name.empty() && name.find_first_of("&#+!") == 0)
	{
		if (name.length() <= 50)
		{
			if (this->channels.find(name) == this->channels.end())
			{
				this->channels[name] = new Channel(name, "");
				std::cout << "Channel " << name << " has been created." << std::endl;
			}
			else
				std::cout << "Channel " << name << "already exists." << std::endl;
			if (this->channels[name]->getUsers().empty())
			{
				this->channels[name]->addUser(user);
				std::cout << "User " << user.getNickname() << " is the operator of channel " << name << std::endl;
			}
			if (this->channels[name]->setInviteOnlyMode() && !this->channels[name]->isOperator(user))
			{
				std::cout << "User " << user.getNickname() << ":Cannot join channel (+i)" << std::endl;
				return ;
			}
			if (std::find(this->channels[name]->getUsers().begin(), this->channels[name]->getUsers().end(), user) == this->channels[name]->getUsers().end())
			{
				this->channels[name]->addUser(user);
				std::cout << "User " << user.getNickname() << " has joined the channel " << name << std::endl;
			}
		}
		else
			std::cout << "Channel name should not exceed 50 chars." << std::endl;
	}
	else
		std::cout << "Invalid channel name." << std::endl;
}

void	Channel::leaveChannel(User user, const std::string &name)
{
	// (void) id, (void) name;
	std::vector<User>::iterator userIt = std::find(this->users.begin(), this->users.end(), user);
    if (userIt != this->users.end())
        this->users.erase(userIt);
}