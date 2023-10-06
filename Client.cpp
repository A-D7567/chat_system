// client.cpp

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "client.h"
#include "user_credentials.h"
#include "handle_server.h"
#include <thread>
#include <cstdlib>

using namespace std;
int client_socket;

Client::~Client()
{
    close(client_socket);
}

void Client::connect_to_server()
{
    UserCredentials local_credentials;
    while (1)
    {
        client_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (client_socket == -1)
        {
            perror("Socket creation failed");
            exit(EXIT_FAILURE);
        }

        sockaddr_in server_address;
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(PORT);
        server_address.sin_addr.s_addr = inet_addr("172.25.4.13");

        if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
        {
            perror("Connection failed");
            exit(EXIT_FAILURE);
        }

        char message[1024];

        thread th1([&local_credentials,client_socket]() {local_credentials.user_credentials(client_socket);});

        th1.join();
       // cout<<"\nsockect is about to close \n";
        close(client_socket);
    }
}

int main()
{
    system("clear");
    Client client;
    client.connect_to_server();
    return 0;
}