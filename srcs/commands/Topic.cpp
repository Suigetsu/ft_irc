#include "../includes/Topic.hpp"
#include "../includes/Server.hpp"

Topic::Topic() : Command::Command()
{
	
}

Topic::~Topic()
{

}

int	Topic::doesUserExist(std::map<int, User *> &usrs, std::string nick) const
{
	std::map<int, User *>::iterator it = usrs.begin();
	while (it != usrs.end())
	{
		if (it->second->getNickname() == nick)
			return it->second->getFd();
		it++;
	}
	return -1;
}

bool	Topic::doesChanExist(std::map<std::string, Channel *> &chan, std::string name) const
{
	std::map<std::string, Channel *>::iterator it = chan.begin();
	while (it != chan.end())
	{
		if (it->second->getName() == name)
			return true;
		it++;
	}
	return false;
}

std::vector<std::string> Topic::parseTopic(std::string command) const
{
	std::istringstream iss(command);
	std::string token;
	std::vector<std::string> param;
	while (std::getline(iss, token, ' '))
	{
		param.push_back(token);
	}
	return (param);
}

void	Topic::sendTopic(Channel *chan, User *user, int fd) const
{
	if (!chan->getTopic().empty())
	{
		send(fd, RPL_TOPIC(user->getNickname(), chan->getName(), chan->getTopic()).c_str(), \
			RPL_TOPIC(user->getNickname(), chan->getName(), chan->getTopic()).length(), 0);
		return ;
	}
	send(fd, RPL_NOTOPIC(user->getNickname(), chan->getName()).c_str(), \
		RPL_NOTOPIC(user->getNickname(), chan->getName()).length(), 0);
}

void	Topic::setTopic(User *user, Channel **chan, std::string topic, int fd) const
{
	if ((*chan)->getTopicStatus() == true)
	{
		if ((*chan)->isOperator(user->getNickname()) == true)
		{
			send(fd, ERR_CHANOPRIVSNEEDED(user->getNickname(), (*chan)->getName()).c_str(), \
				ERR_CHANOPRIVSNEEDED(user->getNickname(), (*chan)->getName()).length(), 0);
			return ;
		}
	}
	topic.erase(0, topic.find(" ") + 1);
	(*chan)->setTopic(topic);
	(*chan)->broadcastToMembers(TOPIC(user->getNickname(), user->getUsername(), user->getHost(), \
		(*chan)->getName(), topic));
}

void	Topic::execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const
{
	if (users[fd]->getCommand().size() < 2)
	{
		send(fd, ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).c_str(), \
			ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).length(), 0);
		throw (Topic::unknownCommandException());
	}
	std::vector<std::string> args = this->parseTopic(users[fd]->getCommand()[FIRST_PARAM]);
	if (this->doesChanExist(chan, args[0]) == false)
	{
		send(fd, ERR_NOSUCHCHANNEL(users[fd]->getNickname(), args[0]).c_str(), \
			ERR_NOSUCHCHANNEL(users[fd]->getNickname(), args[0]).length(), 0);
		throw (Topic::unknownCommandException());
	}
	if (chan[args[0]]->isWithinChannel(users[fd]->getNickname()) != false)
	{
		send(fd, ERR_NOTONCHANNEL(users[fd]->getNickname(), args[0]).c_str(), \
			ERR_NOTONCHANNEL(users[fd]->getNickname(), args[0]).length(), 0);
		throw (Topic::unknownCommandException());
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