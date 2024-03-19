#include "../includes/Invite.hpp"

Invite::Invite() : Command::Command()
{
	
}

Invite::~Invite()
{

}

void	Invite::parseInput(std::vector<std::string> &parsedArgs, std::string param) const
{
	std::istringstream iss(param);
	std::string token;
	if (param.find(' ') == std::string::npos)
	{
		parsedArgs.push_back(param);
		return ;
	}
	while (std::getline(iss, token, ' '))
	{
		parsedArgs.push_back(token);
	}
}

int	Invite::doesUserExist(std::map<int, User *> &usrs, std::string nick) const
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

bool	Invite::doesChanExist(std::map<std::string, Channel *> &chan, std::string name) const
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

void	Invite::execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const
{
	std::vector<std::string> parsedArgs;
	int invFd;
	if (users[fd]->getCommand().size() < 2)
	{
		send (fd, ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).c_str(), \
			ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).length(), 0);
		return ;
	}
	this->parseInput(parsedArgs, users[fd]->getCommand()[FIRST_PARAM]);
	if (parsedArgs.size() < 2)
	{
		send (fd, ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).c_str(), \
			ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).length(), 0);
		return ;
	}
	invFd = this->doesUserExist(users, parsedArgs[0]);
	if (invFd == -1)
	{
		send (fd, ERR_NOSUCHNICK(users[fd]->getNickname(), parsedArgs[0]).c_str(), \
			ERR_NOSUCHNICK(users[fd]->getNickname(), parsedArgs[0]).length(), 0);
		return ;
	}
	if (this->doesChanExist(chan, parsedArgs[1]) == false)
	{
		send (fd, ERR_NOSUCHCHANNEL(users[fd]->getNickname(), parsedArgs[1]).c_str(), \
			ERR_NOSUCHCHANNEL(users[fd]->getNickname(), parsedArgs[1]).length(), 0);
		return ;
	}
	if (chan[parsedArgs[1]]->isWithinChannel(users[fd]->getNickname()) == false)
	{
		send (fd, ERR_NOTONCHANNEL(users[fd]->getNickname(), parsedArgs[1]).c_str(), \
			ERR_NOTONCHANNEL(users[fd]->getNickname(), parsedArgs[1]).length(), 0);
		return ;
	}
	if (chan[parsedArgs[1]]->getInviteStatus() == true && !chan[parsedArgs[1]]->isOperator(users[fd]->getNickname()))
	{
		send (fd, ERR_CHANOPRIVSNEEDED(users[fd]->getNickname(), parsedArgs[1]).c_str(), \
			ERR_CHANOPRIVSNEEDED(users[fd]->getNickname(), parsedArgs[1]).length(), 0);
		return ;
	}
	if (chan[parsedArgs[1]]->isWithinChannel(parsedArgs[0]))
	{
		send (fd, ERR_USERONCHANNEL(users[fd]->getNickname(), parsedArgs[0], parsedArgs[1]).c_str(), \
			ERR_USERONCHANNEL(users[fd]->getNickname(), parsedArgs[0], parsedArgs[1]).length(), 0);
		return ;
	}
	chan[parsedArgs[1]]->addInvitedUsers(parsedArgs[0]);
	send(invFd, INVITE(users[fd]->getNickname(), users[fd]->getUsername(), \
		users[fd]->getHost(), parsedArgs[0], parsedArgs[1]).c_str(), \
		INVITE(users[fd]->getNickname(), users[fd]->getUsername(), \
		users[fd]->getHost(), parsedArgs[0], parsedArgs[1]).length(), 0);
	send (fd, RPL_INVITING(users[fd]->getNickname(), parsedArgs[0], parsedArgs[1]).c_str(), \
		RPL_INVITING(users[fd]->getNickname(), parsedArgs[0], parsedArgs[1]).length(), 0);
}

Invite	*Invite::clone() const
{
	return (new Invite);
}