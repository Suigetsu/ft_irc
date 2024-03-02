/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:19:56 by hrahmane          #+#    #+#             */
/*   Updated: 2024/03/02 10:12:35 by hrahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <vector>
#include <algorithm>

class Channel
{
    private:
        std::string name;
        std::string password;
        std::string topic;
        std::string mode;
        std::vector<User *> users;
        std::vector<int> chanops;
    public:
        Channel();
        Channel(const std::string &name, std::string &password);
        const std::string getName() const;
        const std::string getPassword() const;
        const std::string getTopic() const;
        const std::vector<int> &getUsers() const;
        void  addUser(int id);
        void  removeUser(int id);
        bool  isOperator(int id);
};

#endif