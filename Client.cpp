// Client.cpp
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

const char *addr = "172.21.64.1";

int main() {
    int clientSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr;

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Error in socket");
        exit(1);
    }
    std::cout << "Client socket created..." << std::endl;

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(2000);
    serverAddr.sin_addr.s_addr = inet_addr(addr);

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error in connection");
        exit(1);
    }
    std::cout << "Connected to server..." << std::endl;

    // Main chat loop
while (true) {
    std::cout << "Client: ";
    std::cin.getline(buffer, sizeof(buffer));
    send(clientSocket, buffer, strlen(buffer), 0);

    if (strcmp(buffer, "exit") == 0) {
        std::cout << "Exiting..." << std::endl;
        break;
    }

    memset(buffer, 0, sizeof(buffer)); // Clear the buffer
    ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived < 0) {
        perror("Error in receiving");
        break;
    } else if (bytesReceived == 0) {
        std::cout << "Server disconnected." << std::endl;
        break;
    }

    buffer[bytesReceived] = '\0'; // Null-terminate the received message
    std::cout << "Server: " << buffer << std::endl;
}

    close(clientSocket);

    return 0;
}
