// handle_server.h
//////////////////////////////////////////////////// Header //////////////////////////////////////////////////////////////

// This is the Header File for handle_server.cpp

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SERVERHANDLE_H
#define SERVERHANDLE_H

#include <string>
using namespace std;
extern int client_socket;

class ServerHandler
{
public:
    /*  handle_sent(string username) : Function to Handle Sending messages to the server
        argument-1 : username provided by the user    */
    void handle_send(string username);

    /*  handle_sent(string username) : Function to Handle Recieving messages from the server
        argument-1 : username provided by the user    */
    void handle_rec(string username);

};

#endif // SERVERHANDLE_H