#include "../includes/Command.hpp"

Command::Command()
{

}

Command::~Command()
{

}

const char  *Command::registrationException::what() const throw()
{
    return ("Registration failed");
}

const char  *Command::unknownCommandException::what() const throw()
{
    return ("Unknown command");
}
