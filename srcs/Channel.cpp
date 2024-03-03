/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:54:50 by hrahmane          #+#    #+#             */
/*   Updated: 2024/03/03 13:03:25 by hrahmane         ###   ########.fr       */
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
                std::cout << "Invalid mode: " << mode << std::endl;
                break;
            }
        }
    }
}