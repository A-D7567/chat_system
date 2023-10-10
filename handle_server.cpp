// handle_server.cpp
//////////////////////////////////////////////////// Header //////////////////////////////////////////////////////////////

// In this file contains the handle_send and handle_recieve function to communicate with server

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "handle_server.h"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <cstdlib>
#include <unistd.h>
#include <thread>
#include <cstdlib>

using namespace std;

int flag = 0;

// Function to Handle Sending messages to the server
void ServerHandler::handle_send(string username)
{
    char message[1024]; // Storing Messages Provided by the user and server

    while (1)
    {
        cout << "\r" << username << " : ";

        cin.getline(message, sizeof(message));

        if (strcmp(message, "@exit") == 0)
        {
            cout << "Exiting the program." << endl;
            close(client_socket); // Close the client socket
            exit(0);
        }

        if (flag == 1)
        {
            while (1)
            {

                if (strcmp(message, "@exit") == 0)
                {
                    cout << "Exiting the program." << endl;
                    close(client_socket); // Close the client socket
                    exit(0);
                }

                if (strcmp(message, "@yes") == 0)
                {
                    system("clear");      // Clear the console screen
                    close(client_socket); // Close the client socket
                    flag = 0;
                    break;
                }

                cout << "\nYou have entered wrong input, Please Try Again ( @yes / @exit) :\n";
                cin.getline(message, sizeof(message));
            }
            break;
        }

        send(client_socket, message, strlen(message), 0); // Sending Messages to the server
        memset(message, 0, sizeof(message));
    }
}

// Function to Handle Recieving messages from the server
void ServerHandler::handle_rec(string username)
{
    system("clear"); // Clear the console screen
    char message[1024]; // Storing Messages Provided by the user and server
    while (1)
    {
        memset(message, 0, sizeof(message));

        int bytes_received = recv(client_socket, message, sizeof(message), 0); // Recieving Messages from the server

        int exit_flag = 0;

        if (strcmp(message, "@exit") == 0)
        {
            exit_flag == 1;
            cerr << "\rServer disconnected , program is exiting \n";
            exit(0);
        }

        if (bytes_received <= 0)
        {

            cerr << "\rServer disconnected.";

            close(client_socket); // Close the client socket
            flag = 1;
            cout << "\n\nDo you Want to Try Again ( @yes / @exit) :\n";
            break;
        }

        if (!strcmp(message, "Authentication successful."))
        {

            cout << "\r--------------------------------------------------" << endl;
            cout << "Chat Application Started with : " << username << endl;
            cout << "--------------------------------------------------" << endl;
        }

        cout << "\rServer : " << message << endl;

        write(0, "\r", strlen("\r")); // Move cursor to the beginning of the line
        write(0, username.c_str(), strlen(username.c_str()));
        write(0, " : ", strlen(" : "));
    }
}
