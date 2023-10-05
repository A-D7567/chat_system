// server.h
#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <vector>
#include <netinet/in.h>
#include "user_auth.h"
#include "handle_clients.h"

const int PORT = 1124;
const int MAX_CONNECTIONS = 5;
const int MAX_BUFFER_SIZE = 1024;

class Server
{
public:
    Server();
    ~Server();
    void start_Client_socket();

private:
    int server_socket;
    vector<int> client_sockets;
    UserManager userManager;
};

#endif // SERVER_H
