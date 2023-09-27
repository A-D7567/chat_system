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

char buffer[1024];
string username;

void handel_signup(int client_socket)
{

    // Handle sign-up
    // send(client_socket, "Enter a new username: ", strlen("Enter a new username: "), 0);

    memset(buffer, 0, sizeof(buffer));
    int username_length = recv(client_socket, buffer, sizeof(buffer), 0);

    if (username_length <= 0)
    {
        cout << "Enter Valid Username.." << endl;
        close(client_socket);
        return;
    }

    string new_username(buffer, username_length);

     //send(client_socket, "Enter a new password: ", strlen("Enter a new password: "), 0);
    memset(buffer, 0, sizeof(buffer));

    int password_length = recv(client_socket, buffer, sizeof(buffer), 0);

    if (password_length <= 0)
    {
        cout << "Enter valid Password.." << endl;
        close(client_socket);
        return;
    }

    string new_password(buffer, password_length);
    if(!isUsernameTaken(new_username))
    {
    UserData new_user;
    new_user.username = new_username;
    new_user.password = new_password;
    user_data.push_back(new_user);
    saveUserFile();

    send(client_socket, "Signup successful.", strlen("Signup successful."), 0);

    }
    else
    {
        cout<< " username is already taken......." << endl ;
        close(client_socket);
    }
}

void handel_login(int client_socket)
{  

    // Handle login
    //send(client_socket, "Enter username: ", strlen("Enter username: "), 0);

    memset(buffer, 0, sizeof(buffer));
    int username_length = recv(client_socket, buffer, sizeof(buffer), 0);

    if (username_length <= 0)
    {
        cout << "Enter Valid Username.." << endl;
        close(client_socket);
        return;
    }

    string client_username(buffer, username_length);
    //send(client_socket, "Enter password: ", strlen("Enter password: "), 0);
    memset(buffer, 0, sizeof(buffer));

    int password_length = recv(client_socket, buffer, sizeof(buffer), 0);

    if (password_length <= 0)
    {
        cout << "Enter valid Password.." << endl;
        close(client_socket);
        return;
    }

    string client_password(buffer, password_length);

    if (authenticateUser(client_username, client_password))
    {
        username = client_username;
        send(client_socket, "Authentication successful.", strlen("Authentication successful."), 0);
    }
    else
    {
        send(client_socket, "Authentication failed. Try again.", strlen("Authentication failed. Try again."), 0);
        close(client_socket);
    }
}


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

        if (strcmp(buffer, "login") == 0)
        {
            // Handle login
            handel_login(client_socket);
        }
        else if (strcmp(buffer, "signup") == 0)
        {
            // Handle sign-up
            handel_signup(client_socket);
            
        }
        cout << "\r" <<username << " : " << buffer << endl;
        // else
        // {
        //     send(client_socket, "Authentication required.", strlen("Authentication required."), 0);
        // }
    }
}

void handle_send(int client_socket)
{
    char buffer[1024];
    while (1)
    {
        cout << "Server : ";
        cin.getline(buffer, sizeof(buffer));

        if (strcmp(buffer, "q") == 0)
        {
            break;
        }

        send(client_socket, buffer, strlen(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
    }
}

void handle_client(int client_socket)
{
    char buffer[1024];
    cout << "_________________________________________________" << client_socket << "\n";
    cout << "Successfully connected to client " << client_socket << "\n";
    cout << "_________________________________________________" << client_socket << "\n";
  
    thread(handle_rec, client_socket).detach();
    thread(handle_send, client_socket).detach();
   
}
