// handle_clients.h
#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <string>
#include "user_auth.h"

using namespace std;

//extern vector<UserData> user_data;
class Clienthandler
{
    public:
    int client_socket;
    Clienthandler(int clientsocket)
    {
        client_socket = clientsocket;
    }

    char buffer[1024];
    string username;

    int handle_client();
    int handel_signup();
    int handel_login();
    void handle_rec();
    void handle_send();

};

#endif // CLIENT_HANDLER_H