// server.h

//////////////////////////////////////////////////// Header ///////////////////////////////////////////////////////////////////////
/*  Header file for server.cpp where all server releated classes and macros are decleare for the client - server project

classes decleare here are : Server
Macros decleare here are : PORT , MAX_CONNECTIONS, MAX_BUFFER_SIZE

 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <vector>
#include <netinet/in.h>
#include "user_auth.h"
#include "handle_clients.h"

const int PORT = 1126;        // Port for the communication between client and server
const int MAX_CONNECTIONS = 5;  // max number of connection in queue by litention systemcall
const int MAX_BUFFER_SIZE = 1024;  //max size of the buffer

class Server
{
public:
    ~Server();                  // distructor for the calss Server
    void start_Client_socket(); // This function create the socket and Accepts the client request

private:
    int server_socket;          // store the FD of the Server_socket
    vector<int> client_sockets; // vector to store the conected clients
    UserManager local_user;     // This object of Class UserManager is responsible for loading and storing the data on user file
};

#endif // SERVER_H