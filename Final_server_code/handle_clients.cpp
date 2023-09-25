#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <unistd.h>
#include "server.h"
#include "user_auth.h"
#include "handle_clients.h"
using namespace std;

extern vector<UserData> user_data;

void handle_rec(int client_socket)
{
    char buffer[1024];
    while (1)
    {
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0)
        {
            close(client_socket);
            return;
        }

        cout << "client: " << buffer << endl;

        // Add logic to process client messages here

        if (strcmp(buffer, "login") == 0)
        {
            // Handle login
            char username[1024];
            char password[1024];

            int bytes_received_username = recv(client_socket, username, sizeof(username), 0);
            int bytes_received_password = recv(client_socket, password, sizeof(password), 0);

            if (bytes_received_username <= 0 || bytes_received_password <= 0)
            {
                cout << "username and password not recieved." << endl;
                continue;
            }

            // Authenticate the user
            if (authenticateUser(username, password))
            {
                send(client_socket, "Authentication successful", strlen("Authentication successful"), 0);
                cout << "Authentication successful for user: " << username << endl;
            }
            else
            {
                send(client_socket, "Authentication failed", strlen("Authentication failed"), 0);
                cout << "Authentication failed for user: " << username << endl;
            }
        }
        else if (strcmp(buffer, "signup") == 0)
        {
            // Handle sign-up
            char new_username[1024];
            char new_password[1024];

            int bytes_received_new_username = recv(client_socket, new_username, sizeof(new_username), 0);
            int bytes_received_new_password = recv(client_socket, new_password, sizeof(new_password), 0);

            if (bytes_received_new_username <= 0 || bytes_received_new_password <= 0)
            {
                cout << "Error receiving new username and password." << endl;
                continue;
            }

            // Check if the username is already taken
            if (isUsernameTaken(new_username))
            {
                send(client_socket, "Username is already taken", strlen("Username is already taken"), 0);
                cout << "Username is already taken: " << new_username << endl;
            }
            else
            {
                UserData new_user;
                new_user.username = new_username;
                new_user.password = new_password;
                user_data.push_back(new_user);

                send(client_socket, "Sign-up successful", strlen("Sign-up successful"), 0);
                cout << "Sign-up successful for user: " << new_username << endl;
            }
        }
        else
        {
            break;
        }
    }
}

void handle_send(int client_socket)
{
    char buffer[1024];
    while (1)
    {
        cout << "server : ";
        cin.getline(buffer, sizeof(buffer));

        if (strcmp(buffer, "q") == 0)
        {
            break;
        }

        send(client_socket, buffer, strlen(buffer), 0);
    }
}

void handle_client(int client_socket)
{
    char buffer[1024];
    cout << "_________________________________________________" << client_socket << "\n";
    cout << "Successfully connected to client " << client_socket << "\n";
    cout << "_________________________________________________" << client_socket << "\n";

    thread(handle_send, client_socket).detach();
    thread(handle_rec, client_socket).detach();
 
 }
