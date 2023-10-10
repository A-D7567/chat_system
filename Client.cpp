// client.cpp
//////////////////////////////////////////////////// Header //////////////////////////////////////////////////////////////

/*      In this file contains the main function and Client side impelementations for the client - server project        */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

int client_socket; // storing fd of the client socket

// Client Distructor
Client::~Client()
{
    close(client_socket); // Closing Client Socket
}

// Function for connect Client to the Server
void Client::connect_to_server()
{
    UserCredentials local_credentials; // Object of the User Credentials Class

    while (1)
    {
        client_socket = socket(AF_INET, SOCK_STREAM, 0); // Creating Client Socket
        if (client_socket == -1)
        {
            perror("Socket creation failed");
            exit(EXIT_FAILURE);
        }

        sockaddr_in server_address;                                // Structure to store server address information
        server_address.sin_family = AF_INET;                       // Set address family to IPv4
        server_address.sin_port = htons(PORT);                     // Set port number using host-to-network short function
        server_address.sin_addr.s_addr = inet_addr("172.25.4.13"); // Set server IP address

        if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) // Attempting to connect to the server
        {
            perror("Connection failed");
            exit(EXIT_FAILURE);
        }
        // Starting client thread for user credentials handling (sending and receiving data)
        thread start_client_thread([=,&local_credentials]()
                                   { local_credentials.user_credentials(client_socket); });

        start_client_thread.join();

        close(client_socket); // closing client socket
    }
}

// Main Function
int main()
{
    system("clear");            // Clear the console screen
    Client client;              // object of the Client Class
    client.connect_to_server(); // Calling the function to connect client to the server
    return 0;
}