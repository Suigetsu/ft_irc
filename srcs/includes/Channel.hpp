/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:19:56 by hrahmane          #+#    #+#             */
/*   Updated: 2024/03/09 16:07:23 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include "User.hpp"
#include "RPL.hpp"
#include "ERR.hpp"

# define BACKLOG 10

class Channel
{
    private:
        std::string name;
        std::string password;
        std::string topic;
        std::string mode;
        std::vector<User*> users;
        std::vector<std::string> chanops;
        int userLimit;
        bool inviteStatus;
        bool topicStatus;
        bool limitStatus;
        bool keyStatus;
        
    public:
        Channel();
        Channel(const std::string &name);
        Channel(const std::string &name, const std::string &password);
        const std::string getName() const;
        const std::string getPassword() const;
        const std::string getTopic() const;
        const std::vector<User*> &getUsers() const;
        void  setOperator(User *user);
        void  addUser(User *user);
        void  removeUser(User *user);
        bool  isOperator(User *user) const;
        bool  isNameValid(const std::string &name);
        void  kickUser(User *op, User *user);
        void  inviteUser(User *op, User *user);
        void  setTopic(User *op, const std::string &topic);
        void  setMode(User *op, const std::string &mode);
        bool  setInviteOnlyMode();
        bool  setTopicRestriction();
        bool  setChannelKey();
        bool  grantOperatorPriv();
        void  setUserLimit(int limit);
        void  leaveChannel(User *user, const std::string &name);
        void    joinChannel(std::map<int, User*> users, int fd);
        void  joinChannel(std::map<int, User*> users, int fd, std::string key);
        size_t   getUserLimit();
        Channel *clone(const std::string &name) const;
        void    createChannel(std::map<int, User*> users, int fd);
        bool    getLimitStatus();
        bool    getKeyStatus();
        bool    getTopicStatus();
        bool    getInviteStatus();
        const std::string    bufferizeNames() const;
};

#endif