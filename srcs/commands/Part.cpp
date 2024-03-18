#include "../includes/Part.hpp"

Part::Part() : Command::Command()
{
	
}

Part::~Part()
{

}

std::vector<std::string>	Part::parseChansToPart(const std::string &list) const
{
	std::vector<std::string> chans;
	std::istringstream iss(list);
	std::string token;
	while (std::getline(iss, token, ','))
	{
		chans.push_back(token);
	}
	return (chans);
}

void	Part::parseInput(std::vector<std::string> &chanVec, std::string &text, std::string param) const
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

void	Part::execute(std::map<int, User *> &users, std::map<std::string, Channel *> &chan, int fd) const
{
	std::vector<std::string> chanVec;
	std::string reason;
	if (users[fd]->getCommand().size() < 2)
	{
		send (fd, ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).c_str(), \
			ERR_NEEDMOREPARAMS(users[fd]->getNickname(), users[fd]->getCommand()[COMMAND]).length(), 0);
		return ;
	}
	this->parseInput(chanVec, reason, users[fd]->getCommand()[FIRST_PARAM]);
}

Part	*Part::clone() const
{
	return (new Part);
}