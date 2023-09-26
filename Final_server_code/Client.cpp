//client.cpp
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <thread>
#include <netinet/in.h>
#include <unistd.h>

constexpr int PORT = 3339;
using namespace std;

int client_socket;

void handle_send(int client_socket)
{
    char message[1024];

    while (1)
    {
        cout << "Client : ";
        cin.getline(message, sizeof(message));

        if (strcmp(message, "q") == 0)
        {
            close(client_socket);
            exit(0);
        }

        send(client_socket, message, strlen(message), 0);
        memset(message, 0, sizeof(message));
    }
}

void handle_rec(int client_socket)
{
    char message[1024];

    while (1)
    {
        memset(message, 0, sizeof(message));
        write(0, "hello how are you all\n", strlen("\n"));
        int bytes_received = recv(client_socket, message, sizeof(message), 0);
        if (bytes_received <= 0)
        {
            cerr << "\rServer disconnected." << endl;
            close(client_socket);
            exit(1);
        }
        cout << "\r Server : " << message <<endl;
       

    }
}

int main()
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
    server_address.sin_addr.s_addr = INADDR_ANY;//inet_addr("172.20.104.240");

    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    char message[1024];


//while (1)
{
    int choice;

    cout << "Select an option:" << endl;
    cout << "1. Login" << endl;
    cout << "2. Signup" << endl;
    cout << "3. Quit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    
    cin.ignore();

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

        thread(handle_send, client_socket).detach();
        thread(handle_rec, client_socket).detach();
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

        thread(handle_send, client_socket).detach();
        thread(handle_rec, client_socket).detach();
    }
    else if (choice == 3)
    {
        // Quit
        cout << "Exiting the program." << endl;
        exit(0);
    }
    else
    {
        cout << "Invalid choice. Please select 1, 2, or 3." << endl;
    }

    while(1);

}


    close(client_socket);
    return 0;
}