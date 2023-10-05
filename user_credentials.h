// user_credentials.h
#ifndef USER_CREDENTIALS_H
#define USER_CREDENTIALS_H

#include <iostream>
#include <string>
using namespace std;

class UserCredentials
{
public:
    int choice = 0;
    string input;
    UserCredentials(){

    }
    void user_credentials(int client_socket);
};

#endif // USER_CREDENTIALS_H
