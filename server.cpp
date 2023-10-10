// server.cpp

//////////////////////////////////////////////////// Header ///////////////////////////////////////////////////////////////
/*       In this file contains the main function and some server side function impelementations of the client - server project
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <unistd.h>
#include <thread>
#include "server.h"
#include "user_auth.h"
#include "handle_clients.h"
#include <unistd.h>

using namespace std;

extern vector<UserData> user_data; // Vector to store the user data

Server::~Server() // distructor for the calss Server
{
    close(server_socket);
    local_user.saveUserFile();
}

void Server::start_Client_socket() // This function create the socket and Accepts the client request
{
    local_user.loadUserFile();                          // load the user_credential data from the file
    int server_socket = socket(AF_INET, SOCK_STREAM, 0); // creating the socket for the server

    if (server_socket == -1)
    {
        perror("Socket creation failed");
        exit(0);
    }

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) // binding the server data with socket created
    {
        perror(" Binding failed ");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, MAX_CONNECTIONS) == -1) // strat listing for the client request
    {
        perror(" Listening failed ");
        exit(EXIT_FAILURE);
    }
    cout << " Server listening on port " << PORT << endl;

    while (true)
    {
        sockaddr_in client_address;
        socklen_t client_addr_len = sizeof(client_address);

        int client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_addr_len);
        Clienthandler local_client(client_socket);

        if (client_socket == -1)
        {
            perror(" Accepting connection failed ");
            continue;
        }

        client_sockets.push_back(client_socket);

        thread handle_client([&local_client]()
                             { local_client.handle_client(); }); // Creating the thread to handle the client

        handle_client.join(); // program is waiting for thread to join ;
    }
}

int main()
{
    Server server;
    server.start_Client_socket();
    return 0;
}