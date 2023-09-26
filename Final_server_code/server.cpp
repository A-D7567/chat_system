// server.cpp
#include <iostream>
#include <vector>
#include <unistd.h>
#include <thread>
#include "server.h"
#include "user_auth.h"
#include "handle_clients.h"


using namespace std;
extern vector<UserData> user_data;

int main()
{
    vector<int> client_sockets;

    loadUserFile();

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        perror("Socket creation failed");
        exit(0);
    }

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, MAX_CONNECTIONS) == -1)
    {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }

    cout << "Server listening on port " << PORT << endl;

    while (true)
    {
        sockaddr_in client_address;
        socklen_t client_addr_len = sizeof(client_address);

        int client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_addr_len);
        if (client_socket == -1)
        {
            perror("Accepting connection failed");
            continue;
        }
        client_sockets.push_back(client_socket);

        // Thread to handle the client
        thread(handle_client, client_socket).detach();
    }
    close(server_socket);
    saveUserFile(); // Save user data
    return 0;
}