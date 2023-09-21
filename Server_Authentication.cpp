// server.cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <map>
#include <vector>
#include <thread>
#include <fstream>
const int PORT = 2222;
const int MAX_CONNECTIONS = 5;
const int MAX_BUFFER_SIZE = 1024;

using namespace std;

// user data structure
struct UserData
{
    string username;
    string password;
};

// User database using a map
map<std::string, UserData> userDatabase;
vector<UserData> user_data;
vector<int> client_sockets;

// Read file User.txt
void loadUserFile()
{
    ifstream userFile("users.txt");
    if (!userFile.is_open())
    {
        cout << "Error opening user file." << endl;
        return;
    }
    UserData user;
    while (userFile >> user.username >> user.password)
    {
        user_data.push_back(user);
    }
    userFile.close();
}

// Write file user.txt
void saveUserFile()
{
    ofstream userFile("users.txt");
    if (!userFile.is_open())
    {
        cout << "Error opening user file." << endl;
        return;
    }
    for (const UserData &user : user_data)
    {
        userFile << "User_Name : " << user.username << "  Password : " << user.password << endl;
    }
    userFile.close();
}

bool authenticateUser(const string &username, const string &password)
{
    for (const UserData &user : user_data)
    {
        if (user.username == username && user.password == password)
        {
            return true; // Authentication successful
        }
    }
    return false; // Authentication failed
}

bool isUsernameTaken(const string &username)
{
    for (const UserData &user : user_data)
    {
        if (user.username == username)
        {
            return true; // Username is already taken
        }
    }
    return false; // Username is available
}

void handle_client(int client_socket)
{
    char buffer[MAX_BUFFER_SIZE];
    bool authenticated = false;
    string username;

    while (true)
    {
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0)
        {
            close(client_socket);
            return;
        }

        if (!authenticated)
        {
            string message(buffer);
            if (message == "login")
            {
                send(client_socket, "Enter username: ", strlen("Enter username: "), 0);
                memset(buffer, 0, sizeof(buffer));
                int username_length = recv(client_socket, buffer, sizeof(buffer), 0);

                if (username_length <= 0)
                {
                    cout << "Enter Valid Username.." << endl;
                    close(client_socket);
                    return;
                }
                string client_username(buffer, username_length);

                send(client_socket, "Enter password: ", strlen("Enter password: "), 0);
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
                    authenticated = true;
                    username = client_username;
                    send(client_socket, "Authentication successful.", strlen("Authentication successful."), 0);
                }
                else
                {
                    send(client_socket, "Authentication failed. Try again.", strlen("Authentication failed. Try again."), 0);
                }
            }
            else if (message == "signup")
            {
                send(client_socket, "Enter a new username: ", strlen("Enter a new username: "), 0);
                memset(buffer, 0, sizeof(buffer));
                int username_length = recv(client_socket, buffer, sizeof(buffer), 0);
                if (username_length <= 0)
                {
                    cout << "Enter Valid Username.." << endl;
                    close(client_socket);
                    return;
                }
                string new_username(buffer, username_length);

                send(client_socket, "Enter a new password: ", strlen("Enter a new password: "), 0);
                memset(buffer, 0, sizeof(buffer));
                int password_length = recv(client_socket, buffer, sizeof(buffer), 0);
                if (password_length <= 0)
                {
                    cout << "Enter valid Password.." << endl;
                    close(client_socket);
                    return;
                }
                string new_password(buffer, password_length);
                UserData new_user;
                new_user.username = new_username;
                new_user.password = new_password;
                user_data.push_back(new_user);
                saveUserFile();
                send(client_socket, "Signup successful.", strlen("Signup successful."), 0);
            }
            else
            {
                send(client_socket, "Authentication required.", strlen("Authentication required."), 0);
            }
        }
        else
        {
            // Chat function
            while (true)
            {
                memset(buffer, 0, sizeof(buffer));
                int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
                if (bytes_received <= 0)
                {
                    close(client_socket);
                    client_sockets.erase(std::remove(client_sockets.begin(), client_sockets.end(), client_socket), client_sockets.end());
                    return;
                }

                // Message to client
                for (int socket : client_sockets)
                {
                    if (socket != client_socket)
                    {
                        send(socket, (username + ": " + std::string(buffer)).c_str(), bytes_received, 0);
                    }
                }
            }
        }
    }
}

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
        std::thread(handle_client, client_socket).detach();
    }
    close(server_socket);
    saveUserFile(); // Save user data
    return 0;
}