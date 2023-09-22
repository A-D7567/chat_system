#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <vector>

using namespace std;

constexpr int PORT = 22211;
constexpr int MAX_CONNECTIONS = 5;

vector<int> client_sockets;


int flag;


void handle_rec(int client_socket)
{
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(client_socket , &read_fds);

    char buffer[1024];
    while(1)
    {
//	select(client_socket + 0 , &read_fds, NULL, NULL, NULL);   
        memset(buffer, 0, sizeof(buffer));
        flag =0;
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        flag=1;
        if (bytes_received <= 0) 
        {
            close(client_socket);
            return;
        }
       cout << "\rclient : " << buffer << endl ; 
     


    }
}

void handle_send(int client_socket)
{
    char buffer[1024];
    while(1)
    { 
       

	    cout << "server : ";
        memset(buffer, 0, sizeof(buffer));
        cin.getline(buffer, sizeof(buffer));
        // if(flag)
        // {
        //      cout << "server : ";
        // }

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
    cout << "Sucessfully connected to client " << client_socket << "\n";
    cout << "_________________________________________________" << client_socket << "\n";
    //while (true) 
    {
        thread(handle_send, client_socket).detach();
        thread(handle_rec, client_socket).detach();
    }
}

int main() 
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, MAX_CONNECTIONS) == -1) {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }
    cout << "Server listening on port " << PORT << endl;


    while (true)
    {
        sockaddr_in client_address;
        socklen_t client_addr_len = sizeof(client_address);

        int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_addr_len);
        if (client_socket == -1) 
        {
            perror("Accepting connection failed");
            continue;
        }

        client_sockets.push_back(client_socket);

        //Create a new thread to handle the client

        thread(handle_client, client_socket).detach();

    }

    close(server_socket);
    return 0;
}
