/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahmane <hrahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:19:56 by hrahmane          #+#    #+#             */
/*   Updated: 2024/03/02 17:18:18 by hrahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include "User.hpp"

class Channel
{
    private:
        std::string name;
        std::string password;
        std::string topic;
        std::string mode;
        std::vector<User> users;
        std::vector<int> chanops;
    public:
        Channel();
        Channel(const std::string &name, const std::string &password);
        const std::string getName() const;
        const std::string getPassword() const;
        const std::string getTopic() const;
        const std::vector<User> &getUsers() const;
        void  addUser(User user);
        void  removeUser(User user);
        bool  isOperator(User user) const;
        void  kickUser(User op, User user);
        void  inviteUser(User op, User user);
        void  setTopic(User op, const std::string &topic);
        void  setMode(User op, const std::string &mode);
        void  setInviteOnlyMode();
        void  setTopicRestriction();
        void  setChannelKey();
        void  grantOperatorPriv();
        void  setUserLimit();
        
};

#endif