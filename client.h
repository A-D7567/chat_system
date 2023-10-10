// client.h
//////////////////////////////////////////////////// Header //////////////////////////////////////////////////////////////

// This is the Header File for Client.cpp

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include <netinet/in.h>
#include "user_credentials.h"
#include "handle_server.h"

using namespace std;
constexpr int PORT = 1126;

class Client
{
public:
    ~Client();                // Client Distructor
    void connect_to_server(); // Function for connect Client to the Server
};

#endif // CLIENT_H