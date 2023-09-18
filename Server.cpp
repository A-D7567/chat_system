// Server.cpp
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int serverSocket, newSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr, newAddr;
    socklen_t addr_size;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Error in socket");
        exit(1);
    }
    std::cout << "Server socket created..." << std::endl;

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("10.126.65.66") 	;

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error in binding");
        exit(1);
    }
    std::cout << "Binding success..." << std::endl;

    if (listen(serverSocket, 10) == 0) {
        std::cout << "Listening..." << std::endl;
    } else {
        std::cout << "Error in listening" << std::endl;
        exit(1);
    }

    addr_size = sizeof(newAddr);
    newSocket = accept(serverSocket, (struct sockaddr*)&newAddr, &addr_size);
    if (newSocket < 0) {
        perror("Error in accepting");
        exit(1);
    }

    // Main chat loop
while (true) {
    memset(buffer, 0, sizeof(buffer)); // Clear the buffer
    ssize_t bytesReceived = recv(newSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived < 0) {
        perror("Error in receiving");
        break;
    } else if (bytesReceived == 0) {
        std::cout << "Client disconnected." << std::endl;
        break;
    }

    buffer[bytesReceived] = '\0'; // Null-terminate the received message
    std::cout << "Client: " << buffer << std::endl;

    memset(buffer, 0, sizeof(buffer)); // Clear the buffer
    std::cout << "Server: ";
    std::cin.getline(buffer, sizeof(buffer));
    send(newSocket, buffer, strlen(buffer), 0);
}



    close(newSocket);
    close(serverSocket);

    return 0;
}

