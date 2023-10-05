#ifndef SERVERHANDLE_H
#define SERVERHANDLE_H

#include <string>
using namespace std;
extern int client_socket;


class ServerHandler
{
public:
    ServerHandler(){}
    void handle_send(string username);
    void handle_rec(string username);
};

#endif // SERVERHANDLE_H
