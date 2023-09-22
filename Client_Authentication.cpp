// client.cpp
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

constexpr int PORT = 2222;

using namespace std;

int main()
{
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Change to the server's IP

    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    char message[1024];
    cout << "Select an option:" << endl;
    cout << "1. Login" << endl;
    cout << "2. Signup" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;
    cin.ignore(); // Clear the newline character from the buffer

    if (choice == 1)
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

        // Receive and handle server's response for login
        memset(message, 0, sizeof(message));
        int bytes_received = recv(client_socket, message, sizeof(message), 0);
        if (bytes_received <= 0)
        {
            cout << "Server disconnected." << endl;
        }
        else
        {
            cout << "Server: " << message << endl;
        }
    }
    else if (choice == 2)
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

        // Receive and handle server's response for signup
        memset(message, 0, sizeof(message));
        int bytes_received = recv(client_socket, message, sizeof(message), 0);
        if (bytes_received <= 0)
        {
            cout << "Server disconnected." << endl;
        }
        else
        {
            cout << "Server: " << message << endl;
        }
    }
    else
    {
        cout << "Invalid choice. Please select 1 or 2." << endl;
    }

    close(client_socket);
    return 0;
}