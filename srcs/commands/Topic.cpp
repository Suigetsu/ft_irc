#include "../includes/Topic.hpp"
#include "../includes/Server.hpp"

Topic::Topic() : Command::Command()
{
	
}

Topic::~Topic()
{

}

int	Topic::doesUserExist(usrsMap &usrs, std::string nick) const
{
	usrsMap::iterator it = usrs.begin();
	while (it != usrs.end())
	{
		if (it->second->getNick() == nick)
			return it->second->getFd();
		it++;
	}
	return -1;
}

bool	Topic::doesChanExist(chanMap &chan, std::string name) const
{
	chanMap::iterator it = chan.begin();
	while (it != chan.end())
	{
		if (it->second->getName() == name)
			return true;
		it++;
	}
	return false;
}

strVector Topic::parseTopic(std::string command) const
{
	strVector param;

	if (command.find(" ") == std::string::npos)
	{
		param.push_back(command);
		return (param);
	}
	param.push_back(command.substr(0, command.find(" ")));
	command.erase(0, command.find(" ") + 1);
	param.push_back(command);
	return (param);
}

void	Topic:: sendTopic(Channel *chan, User *user, int fd) const
{
	if (!chan->getTopic().empty())
	{
		send(fd, RPL_TOPIC(user->getNick(), chan->getName(), chan->getTopic()).c_str(), \
			RPL_TOPIC(user->getNick(), chan->getName(), chan->getTopic()).length(), 0);
		return ;
	}
	send(fd, RPL_NOTOPIC(user->getNick(), chan->getName()).c_str(), \
		RPL_NOTOPIC(user->getNick(), chan->getName()).length(), 0);
}

void	Topic::setTopic(User *user, Channel **chan, std::string topic, int fd) const
{
	if ((*chan)->getTopicStatus() == true)
	{
		if ((*chan)->isOperator(user->getNick()) == false)
		{
			send(fd, ERR_CHANOPRIVSNEEDED(user->getNick(), (*chan)->getName()).c_str(), \
				ERR_CHANOPRIVSNEEDED(user->getNick(), (*chan)->getName()).length(), 0);
			return ;
		}
	}
	topic.erase(0, topic.find(":") + 1);
	if (topic.length() > 490)
		return ;
	(*chan)->setTopic(topic);
	(*chan)->broadcastToMembers(TOPIC(user->getNick(), user->getName(), user->getHost(), \
		(*chan)->getName(), topic));
}

void	Topic::execute(usrsMap &users, chanMap &chan, int fd) const
{
	if (users[fd]->getCommand().size() < 2)
	{
		send(fd, ERR_NEEDMOREPARAMS(users[fd]->getNick(), users[fd]->getCommand()[COMMAND]).c_str(), \
			ERR_NEEDMOREPARAMS(users[fd]->getNick(), users[fd]->getCommand()[COMMAND]).length(), 0);
		return ;
	}
	strVector args = this->parseTopic(users[fd]->getCommand()[FIRST_PARAM]);
	if (this->doesChanExist(chan, args[0]) == false)
	{
		send(fd, ERR_NOSUCHCHANNEL(users[fd]->getNick(), args[0]).c_str(), \
			ERR_NOSUCHCHANNEL(users[fd]->getNick(), args[0]).length(), 0);
		return ;
	}
	if (chan[args[0]]->isWithinChannel(users[fd]->getNick()) == false)
	{
		send(fd, ERR_NOTONCHANNEL(users[fd]->getNick(), args[0]).c_str(), \
			ERR_NOTONCHANNEL(users[fd]->getNick(), args[0]).length(), 0);
		return ;
	}
	if (args.size() == 1)
	{
		this->sendTopic(chan[args[0]], users[fd], fd);
		return ;
	}
	this->setTopic(users[fd], &chan[args[0]], args[1], fd);
}

Topic	*Topic::clone() const
{
	return (new Topic);
}