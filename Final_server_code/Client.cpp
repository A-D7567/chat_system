    // client.cpp
    #include <iostream>
    #include <cstring>
    #include <cstdlib>
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <thread>
    #include <netinet/in.h>
    #include "user_credentials.h"
    #include "handle_server.h"

    using namespace std;
    int client_socket;

    void user_credentials()
    {
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
        server_address.sin_addr.s_addr = INADDR_ANY; // inet_addr("172.20.104.240");

        if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
        {
            perror("Connection failed");
            exit(EXIT_FAILURE);
        }

        char message[1024];

        // while (1)
        user_credentials(client_socket);
        
        close(client_socket);
        return 0;
    }
    ~