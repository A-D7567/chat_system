#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <thread>
#include <netinet/in.h>

constexpr int PORT = 11111;


int client_socket;


void handle_send(int a)
{
    char message[1024];

    while(1)
    {
    std::cout << "Client hello ";
    std::cin.getline(message, sizeof(message));

    if (strcmp(message, "q") == 0) {
          close(client_socket);
    }

    send(client_socket, message, strlen(message), 0);

    memset(message, 0, sizeof(message));
    }

}

void handle_rec(int b)
{
    char message[1024];

    while(1)
    {
    int bytes_received = recv(client_socket, message, sizeof(message), 0);
        if (bytes_received <= 0) {
            std::cerr << "Server disconnected." << std::endl;
             exit(1);
        }

    std::cout << "Server: " << message << std::endl;
    }

}

int main() {
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;//inet_addr("172.25.4.13");

    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) 
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    char message[1024];

    //while (true) 
    {
        
        std::thread(handle_send, 1).detach();
        std::thread(handle_rec, 1).detach();
      
    }
    while(1);
    
    return 0;
}
