// user_credentials.h
//////////////////////////////////////////////////// Header //////////////////////////////////////////////////////////////

// This is the Header File for user_credentials.cpp

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef USER_CREDENTIALS_H
#define USER_CREDENTIALS_H

#include <iostream>
#include <string>

using namespace std;

class UserCredentials
{
public:
    /*  user_credentials(int client_socket) : Function for asking user credentials.
        argument-1 : fd of the client socket.   */
    void user_credentials(int client_socket);

private:
    string input; // user provided choice will be stored in string format
    int choice;   // storing user choice stored in input variable after converting into integer
};

#endif // USER_CREDENTIALS_H