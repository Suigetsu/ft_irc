/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:54:50 by hrahmane          #+#    #+#             */
/*   Updated: 2024/02/28 11:31:33 by hrahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel()
{
    
}

Channel::Channel(const std::string &name, std::string &password) : name(name), password(password)
{

}

const std::string Channel::getName() const
{
    return this->name;
}
const std::vector<int> &Channel::getUsers() const
{
    return this->users;
}

void  Channel::addUser(int id)
{
    if (std::find(users.begin(), users.end(), id) == users.end())
        this->users.push_back(id);
    std::cout << "User is already in the channel." << std::endl;
}

void  Channel::removeUser(int id)
{
    std::vector<int>::iterator it = std::find(users.begin(), users.end(), id);
    if (it != users.end())
    {
        users.erase(it);
        std::cout << "User with ID: " << id << " has been removed from the channel." << std::endl;
    }
    else
        std::cout << "User with ID: " << id << " is not in the channel." << std::endl;
}