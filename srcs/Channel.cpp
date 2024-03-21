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

}

const std::string Channel::getName() const
{
    return this->name;
}
std::vector<User*> &Channel::getUsers()
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

bool    Channel::isChannelEmpty()
{
    if (this->getUsers().empty())
        return true;
    return false;
}

void  Channel::removeUser(User *user)
{
    std::vector<User *>::iterator it = this->users.begin();
    while (it != this->users.end())
    {
        if ((*it)->getNick() == user->getNick())
        {
            this->unsetOperator(user);
            this->users.erase(it);
            return ;
        }
        it++;
    }

}

bool    Channel::isOperator(std::string nick) const
{
    if (std::find(this->chanops.begin(), this->chanops.end(), nick) != this->chanops.end())
        return (true);
    return (false);
}

bool  Channel::setChannelKey(std::string key, int fd, usrsMap &user)
{
    if (!this->getPassword().empty() && key != this->getPassword())
    {
        send (fd, ERR_KEYSET(user[fd]->getNick(), this->getName()).c_str(), \
        ERR_KEYSET(user[fd]->getNick(), this->getName()).length(), 0);
        return false;
    }
    this->password = key;
    return true;
}

int  Channel::setUserLimit(int limit)
{
    if (limit <= 0 || limit > this->userLimit)
        return 1;
    this->userLimit = limit;
    return 0;
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

void    Channel::addInvitedUsers(std::string name)
{
    this->invited.push_back(name);
}

bool    Channel::isUserInvited(std::string name)
{
    if (std::find(this->invited.begin(), this->invited.end(), name) != this->invited.end())
        return true;
    return false;
}

void    Channel::clearInvitedUser(std::string name)
{
    strVector::iterator it = std::find(this->invited.begin(), this->invited.end(), name);
    if (it != this->invited.end())
        this->invited.erase(it);
}

void	Channel::joinChannel(usrsMap users, int fd)
{
    if (this->isWithinChannel(users[fd]->getNick()))
        return ;
    if (this->users.size() + 1 > this->getUserLimit())
    {
        send(fd, ERR_CHANNELISFULL(users[fd]->getNick(), this->name).c_str(), \
            ERR_CHANNELISFULL(users[fd]->getNick(), this->name).length(), 0);
        return ;
    }
    if (this->getInviteStatus() && !isUserInvited(users[fd]->getNick()))
    {
        send(fd, ERR_INVITEONLYCHAN(users[fd]->getNick(), this->name).c_str(), \
            ERR_INVITEONLYCHAN(users[fd]->getNick(), this->name).length(), 0);
        return ;
    }
    if (this->getKeyStatus())
    {
        send(fd, ERR_BADCHANNELKEY(users[fd]->getNick(), this->name).c_str(), \
            ERR_BADCHANNELKEY(users[fd]->getNick(), this->name).length(), 0);
        return ;
    }
    std::string buffer = JOIN(users[fd]->getNick(), users[fd]->getName(), users[fd]->getHost(), this->name) \
			+ RPL_NAMREPLY(users[fd]->getNick(), this->getName(), this->bufferizeNames(), \
            this->getPrefix(users[fd]->getNick())) + RPL_ENDOFNAMES(users[fd]->getNick(), this->name);
	send(fd, buffer.c_str(), buffer.length(), 0);
    std::vector<User *> tmp = this->getUsers();
    std::vector<User *>::iterator it = tmp.begin();
    while (it != tmp.end())
    {
        send((*it)->getFd(), JOIN(users[fd]->getNick(), users[fd]->getName(), users[fd]->getHost(), this->name).c_str(), \
            JOIN(users[fd]->getNick(), users[fd]->getName(), users[fd]->getHost(), this->name).length(), 0);
        it++;
    }
    this->addUser(users[fd]);
    this->clearInvitedUser(users[fd]->getNick());
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

const std::string    Channel::bufferizeNames()
{
    std::string buffer = " ";
    std::vector<User *>::iterator it = this->getUsers().begin();
    while (it != this->getUsers().end())
    {
        buffer += this->getPrefix((*it)->getNick()) + (*it)->getNick();
        if (it + 1 != this->getUsers().end())
            buffer += " ";
        it++;
    }
    return (buffer);
}

void	Channel::joinChannel(usrsMap users, int fd, std::string key)
{
    if (this->isWithinChannel(users[fd]->getNick()))
        return ;
    if (this->users.size() + 1 > this->getUserLimit())
    {
        send(fd, ERR_CHANNELISFULL(users[fd]->getNick(), this->name).c_str(), \
            ERR_CHANNELISFULL(users[fd]->getNick(), this->name).length(), 0);
        return ;
    }
    if (this->getInviteStatus() && !this->isUserInvited(users[fd]->getNick()))
    {
        send(fd, ERR_INVITEONLYCHAN(users[fd]->getNick(), this->name).c_str(), \
            ERR_INVITEONLYCHAN(users[fd]->getNick(), this->name).length(), 0);
        return ;
    }
    if (this->getKeyStatus() && key != this->getPassword())
    {
        send(fd, ERR_BADCHANNELKEY(users[fd]->getNick(), this->name).c_str(), \
            ERR_BADCHANNELKEY(users[fd]->getNick(), this->name).length(), 0);
        return ;
    }
    std::string buffer = JOIN(users[fd]->getNick(), users[fd]->getName(), users[fd]->getHost(), this->name) \
			+ RPL_NAMREPLY(users[fd]->getNick(), this->getName(), \
            this->bufferizeNames(), this->getPrefix(users[fd]->getNick())) \
            + RPL_ENDOFNAMES(users[fd]->getNick(), this->name);
	send(fd, buffer.c_str(), buffer.length(), 0);
    this->broadcastToMembers(JOIN(users[fd]->getNick(), users[fd]->getName(), users[fd]->getHost(), this->name));
    this->addUser(users[fd]);
    this->clearInvitedUser(users[fd]->getNick());
}

void    Channel::broadcastToMembers(std::string message)
{
    std::vector<User *>::iterator it = this->getUsers().begin();
    while (it != this->getUsers().end())
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
    strVector::iterator it = std::find(this->chanops.begin(), this->chanops.end(), user->getNick());
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
    if (this->isOperator(user->getNick()) == false)
        this->chanops.push_back(user->getNick());
}

User *Channel::getUser(std::string nickname)
{
    std::vector<User *>::iterator it = this->getUsers().begin();
    while (it != (this->getUsers()).end())
    {
        if ((*it)->getNick() == nickname)
            return (*it);
        it++;
    }
    return NULL;
}

void    Channel::setTopic(std::string topic)
{
    this->topic = topic;
}

bool    Channel::isWithinChannel(std::string nickname)
{
    if (this->getUser(nickname) == NULL)
        return false;
    return true;
}

void    Channel::unsetChannelKey()
{
    this->password.clear();
}

void    Channel::removePassword(std::string arg, usrsMap &user, int fd)
{
    if (arg != this->getPassword())
    {
        send (fd, ERR_KEYSET(user[fd]->getNick(), this->getName()).c_str(), \
        ERR_KEYSET(user[fd]->getNick(), this->getName()).length(), 0);
        return ;
    }
    this->unsetChannelKey();
    this->setKeyStatus(false);
}

void    Channel::createChannel(usrsMap users, int fd)
{
    this->addUser(users[fd]);
    this->setOperator(users[fd]);
    std::string buffer = JOIN(users[fd]->getNick(), users[fd]->getName(), users[fd]->getHost(), this->getName()) \
			+ RPL_NAMREPLY(users[fd]->getNick(), this->getName(), "", this->getPrefix(users[fd]->getNick())) + \
            RPL_ENDOFNAMES(users[fd]->getNick(), this->name);
	send(fd, buffer.c_str(), buffer.length(), 0);
}
