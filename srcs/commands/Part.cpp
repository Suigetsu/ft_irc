#include "../includes/Part.hpp"

Part::Part() : Command::Command()
{
	
}

Part::~Part()
{

}

int	Part::doesUserExist(usrsMap &usrs, std::string nick) const
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

bool	Part::doesChanExist(chanMap &chan, std::string name) const
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

strVector	Part::parseChansToPart(const std::string &list) const
{
	strVector chans;
	std::istringstream iss(list);
	std::string token;
	while (std::getline(iss, token, ','))
	{
		chans.push_back(token);
	}
	return (chans);
}

void	Part::parseInput(strVector &chanVec, std::string &text, std::string param) const
{
	std::string chans;
	if (param.find(" ") == std::string::npos)
	{
		chanVec.push_back(param.substr(0, param.find("\n")));
		return ;
	}
	chans = param.substr(0, param.find(" "));
	param.erase(0, param.find(" ") + 1);
	text = param.substr(0, param.find("\n"));
	chanVec = this->parseChansToPart(chans);
}

void	Part::removeEmptyChannel(chanMap &chan, std::string name) const
{
	if (chan[name]->isChannelEmpty() == true)
	{
		delete chan[name];
		chan.erase(name);
	}
}

void	Part::sendPart(strVector chanVec, std::string text, User *user, chanMap &chan, int fd) const
{
	std::string buffer;
	strVector::iterator it = chanVec.begin();
	while (it != chanVec.end())
	{
		if (this->doesChanExist(chan, *it))
		{
			if (chan[*it]->isWithinChannel(user->getNick()))
			{
				buffer += PART(user->getNick(), user->getName(), user->getHost(), *it, text);
				chan[*it]->removeUser(user);
				chan[*it]->broadcastToMembers(PART(user->getNick(), user->getName(), user->getHost(), *it, text));
				this->removeEmptyChannel(chan, *it);
			}
			else
				buffer += ERR_NOTONCHANNEL(user->getNick(), *it);
		}
		else
			buffer += ERR_NOSUCHCHANNEL(user->getNick(), *it);
		it++;
	}
	send (fd, buffer.c_str(), buffer.length(), 0);
}

void	Part::execute(usrsMap &users, chanMap &chan, int fd) const
{
	strVector chanVec;
	std::string reason;
	if (users[fd]->getCommand().size() < 2)
	{
		send (fd, ERR_NEEDMOREPARAMS(users[fd]->getNick(), users[fd]->getCommand()[COMMAND]).c_str(), \
			ERR_NEEDMOREPARAMS(users[fd]->getNick(), users[fd]->getCommand()[COMMAND]).length(), 0);
		return ;
	}
	this->parseInput(chanVec, reason, users[fd]->getCommand()[FIRST_PARAM]);
	if (reason.empty())
		reason = PART_MSG;
	this->sendPart(chanVec, reason, users[fd], chan, fd);
}

Part	*Part::clone() const
{
	return (new Part);
}