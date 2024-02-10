#include <iostream>
#include <cstring> 
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

void init(int port)
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        std::cerr << "Error creating socket" << std::endl;
        return ;
    }
    std::cout << "Socket has been created!" << std::endl;

    sockaddr_in serverAddress;
    std::memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

}
