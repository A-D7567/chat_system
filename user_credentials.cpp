// user_credentials.cpp
//////////////////////////////////////////////////// Header //////////////////////////////////////////////////////////////

// In this file contains the user_credentials function for user login and signup

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "user_credentials.h"
#include "handle_server.h"
#include <iostream>
#include <sys/socket.h>
#include <thread>
#include <cstring>
#include <unistd.h>

using namespace std;

// Function for asking user credentials.
void UserCredentials::user_credentials(int client_socket)
{
    ServerHandler local_handle; // Creating ServerHandler object for handling server interactions

    input = to_string(0);
    choice = 0;

    cout << endl;
    cout << "--------------------------------------------------" << endl;
    cout << endl;

    cout << "Select an option:" << endl;
    cout << "1. Login" << endl;
    cout << "2. Signup" << endl;
    cout << "3. Quit" << endl;
    cout << "Enter your choice: ";
    getline(cin, input);

    cout << "--------------------------------------------------" << endl;

    bool isNumber = true; // Variable to track if input is a number
    for (char c : input)
    {
        if (!isdigit(c))
        {
            isNumber = false;
            break;
        }
    }

    if (isNumber)
    {
        choice = stoi(input); // Converting input to integer and store it in the choice variable
        switch (choice)
        {
        case 1:
        {
            // Login Section
            send(client_socket, "login", strlen("login"), 0); // Sending login signal to the server

            // Enter username
            string username;
            cout << "Enter username: ";
            cin >> username;
            send(client_socket, username.c_str(), username.size(), 0); // Sending username to the server

            // Enter password
            string password;
            cout << "Enter password: ";
            cin >> password;
            send(client_socket, password.c_str(), password.size(), 0); // Sending password to the server

            // Starting threads for sending and receiving messages
            thread send([&local_handle, username]()
                        { local_handle.handle_send(username); }); // Thread for sending messages

            sleep(0.2);

            thread rec([&local_handle, username]()
                       { local_handle.handle_rec(username); }); // Thread for receiving messages

            rec.join();
            send.join();

            return ;
            break;
        }
        case 2:
        {
            // Signup Section
            send(client_socket, "signup", strlen("signup"), 0); // Sending signup signal to the server

            // Enter a new username
            string new_username;
            cout << "Enter a new username: ";
            cin >> new_username;
            send(client_socket, new_username.c_str(), new_username.size(), 0); // Sending new username to the server

            // Enter a new password
            string new_password;
            cout << "Enter a new password: ";
            cin >> new_password;
            send(client_socket, new_password.c_str(), new_password.size(), 0); // Sending new password to the server

            // Starting threads for sending and receiving messages
            thread send([&local_handle, new_username]()
                        { local_handle.handle_send(new_username); }); // handle_send thread to send the messages
            sleep(0.2);
            thread rec([&local_handle, new_username]()
                       { local_handle.handle_rec(new_username); }); // handle_recieve thread to revieve the messages

            rec.join();
            send.join();
            break;
        }
        case 3:
        {
            // Quit Section
            cout << "Exiting the program." << endl;
            exit(0);
            break;
        }
        default:
        {
            system("clear"); // Clear the console screen
            cout << "Invalid choice. Please select 1, 2, or 3." << endl;
            break;
        }
        }
    }
    else
    {
        system("clear"); // Clear the console screen
        cout << "Invalid input! Please enter an integer." << endl;
    }
}