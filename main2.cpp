#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

const int PORT = 8080;
const int BACKLOG = 5; //the maximum length of the queue of pending connections

int main()
{
    //store the file descriptors for the server socket and the client socket,
    int serverSocket, clientSocket;
    // store information about the server and client addresses
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Error while creating the socket");
        return 1;
    }
    //set up the address struct:
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    //bind the socket to the specified port:
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
    {
        perror("Error binding socket");
        std::cout << "Binding error details: " << strerror(errno) << std::endl;
        close(serverSocket);
        return 1;
    }
    /*
    listen for incoming connections
    The listen function puts the socket in 
    a passive mode, waiting for incoming connections
    */
    if (listen(serverSocket, BACKLOG) == -1)
    {
        perror("Error while listening for connections");
        close(serverSocket);
        return 1;
    }
    std::cout << "Server is listening on port " << PORT << "..." << std::endl;
    //accept connections and handle them
    while (1)
    {
        if ((clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen) == -1))
        {
            perror("Error while accepting connection");
            continue;
        }
        std::cout << "Connection accepted from " << inet_ntoa(clientAddr.sin_addr) << std::endl;
        //handle the connection
        char buffer[1024];
        int bread;
        bread = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bread == -1)
            perror("Error while reading from the client");
        else if (bread == 0)
            std::cout << "Connection closed by client" << std::endl;
        else
            {
                std::cout << "Received data from client: " << buffer << std::endl;
                const char *resp = "Hello, client! This is server! I received your message!";
                send(clientSocket, resp, strlen(resp), 0);
            }
            //close the client socket
            close(clientSocket);
    }
    close(serverSocket);
    return 0;
}