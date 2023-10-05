// client.h
#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include <netinet/in.h>
#include "user_credentials.h"
#include "handle_server.h"

using namespace std;
constexpr int PORT = 1121;

class Client
{
public:
    Client();
    ~Client();
    void connect_to_server();

};

#endif // CLIENT_H