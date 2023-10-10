// handle_clients.h
#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <string>
#include "user_auth.h"

using namespace std;

// extern vector<UserData> user_data;
class Clienthandler
{
public:
    int client_socket; // storing FD of the client

    /*
        Constructor Takes clientsocket as the argument which recived by accepting the request of the client and
        update calss variable client_socket so that member function can use it.
    */

    Clienthandler(int clientsocket)
    {
        client_socket = clientsocket;
    }

    char buffer[1024]; // bufer to store the revice message
    string username;   // username of  the user is stored in this variable

    // handle_client function starts the send and revice functionality for the client
    int handle_client();

    // For creating a new user this function can be used
    int handel_signup();

    // handel_login function verify and validate the user
    int handel_login();

    // handle_rec function is used to recive data such as messsages, username ,password and etc from the client
    void handle_rec();

    // Send messages from the server to the client
    void handle_send();
};

#endif // CLIENT_HANDLER_H