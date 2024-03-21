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

# define BACKLOG 200

typedef std::map<int, User *> usrsMap;
typedef std::vector<std::string> strVector;

class Channel
{
    private:
        std::string name;
        std::string password;
        std::string topic;
        std::string mode;
        std::string prefix;
        std::vector<User*> users;
        strVector chanops;
        strVector invited;
        int userLimit;
        bool inviteStatus;
        bool topicStatus;
        bool limitStatus;
        bool keyStatus;
        
    public:
        Channel();
        Channel(const std::string &name);
        Channel(const std::string &name, const std::string &password);
        ~Channel();
        const std::string getName() const;
        const std::string getPassword() const;
        const std::string getTopic() const;
        std::vector<User*> &getUsers();
        User *getUser(std::string nickname);
        void  unsetOperator(User *user);
        void  unsetChannelKey();
        void  setOperator(User *user);
        void  addUser(User *user);
        void  removeUser(User *user);
        bool  isOperator(std::string nick) const;
        bool  isNameValid(const std::string &name);
        void  setMode(User *op, const std::string &mode);
        bool  setInviteOnlyMode();
        bool  setTopicRestriction();
        bool  setChannelKey(std::string key, int fd, usrsMap &user);
        bool  grantOperatorPriv();
        int  setUserLimit(int limit);
        void  leaveChannel(User *user, const std::string &name);
        void    joinChannel(usrsMap users, int fd);
        void  joinChannel(usrsMap users, int fd, std::string key);
        size_t   getUserLimit();
        Channel *clone(const std::string &name) const;
        void    addInvitedUsers(std::string name);
        bool    isUserInvited(std::string name);
        void    clearInvitedUser(std::string name);
        void    createChannel(usrsMap users, int fd);
        void    setLimitStatus(bool status);
        void    setKeyStatus(bool status);
        void    setTopicStatus(bool status);
        void    setInviteStatus(bool status);
        bool    isWithinChannel(std::string nickname);
        bool    getLimitStatus() const;
        bool    getKeyStatus() const;
        bool    getTopicStatus() const;
        bool    getInviteStatus() const;
        const std::string bufferizeNames();
        const std::string bufferizeModes() const;
        void    removePassword(std::string arg, usrsMap &user, int fd);
        std::string getPrefix(std::string nick) const;
        void    setTopic(std::string topic);
        void    broadcastToMembers(std::string message);
        bool    isChannelEmpty();
};

#endif