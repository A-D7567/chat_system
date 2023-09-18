#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

constexpr int PORT = 12345;

int main() {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("172.25.4.13");

    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    char message[1024];

    while (true) {
        std::cout << "Enter message (or 'q' to quit): ";
        std::cin.getline(message, sizeof(message));

        if (strcmp(message, "q") == 0) {
            break;
        }

        send(client_socket, message, strlen(message), 0);

        memset(message, 0, sizeof(message));
        int bytes_received = recv(client_socket, message, sizeof(message), 0);
        if (bytes_received <= 0) {
            std::cerr << "Server disconnected." << std::endl;
            break;
        }

        std::cout << "Server: " << message << std::endl;
    }

    close(client_socket);
    return 0;
}