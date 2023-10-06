// user_credentials.cpp
#include "user_credentials.h"
#include "handle_server.h"
#include <iostream>
#include <sys/socket.h>
#include <thread>
#include <cstring>
#include <unistd.h>

using namespace std;

void UserCredentials::user_credentials(int client_socket)
{
    ServerHandler local_handle;
    input = to_string(0);
    choice = 0;
    cout << endl << "--------------------------------------------------" << endl;
    cout << endl << "Select an option:" << endl;
    cout << "1. Login" << endl;
    cout << "2. Signup" << endl;
    cout << "3. Quit" << endl;
    cout << "Enter your choice: ";
    getline(cin, input);
    cout << "--------------------------------------------------" << endl;

    bool isNumber = true;
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
        choice = stoi(input);
        switch (choice)
        {
        case 1:
        {
            // Login
            send(client_socket, "login", strlen("login"), 0);

            // Enter username
            string username;
            cout << "Enter username: ";
            cin >> username;
            send(client_socket, username.c_str(), username.size(), 0);

            // Enter password
            string password;
            cout << "Enter password: ";
            cin >> password;
            send(client_socket, password.c_str(), password.size(), 0);

            thread send([&local_handle, username]()
                        { local_handle.handle_send(username); });
            sleep(0.2);
            thread rec([&local_handle, username]()
                       { local_handle.handle_rec(username); });

            rec.join();
            send.join();

            return;

            break;
        }
        case 2:
        {
            // Signup
            send(client_socket, "signup", strlen("signup"), 0);

            // Enter a new username
            string new_username;
            cout << "Enter a new username: ";
            cin >> new_username;
            send(client_socket, new_username.c_str(), new_username.size(), 0);

            // Enter a new password
            string new_password;
            cout << "Enter a new password: ";
            cin >> new_password;
            send(client_socket, new_password.c_str(), new_password.size(), 0);

            thread send([&local_handle, new_username]()
                        { local_handle.handle_send(new_username); });
            sleep(1);
            thread rec([&local_handle, new_username]()
                       { local_handle.handle_rec(new_username); });

            rec.join();
            send.join();

            break;
        }
        case 3:
        {
            // Quit
            cout << "Exiting the program." << endl;
            exit(0);
            break;
        }
        default:
        {
            system("clear");
            cout << "Invalid choice. Please select 1, 2, or 3." << endl;
            break;
        }
        }
    }
    else
    {
        system("clear");
        cout << "Invalid input! Please enter an integer." << endl;
    }
}