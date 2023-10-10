// user_auth.h

//////////////////////////////////////////////////// Header ///////////////////////////////////////////////////////////////////////
/* 

Header file for user_auth.cpp where all user_auth.cpp releated classes are decleare for the client - server project

classes decleare here are : UserManager
structure  delcleare here are: UserData

*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <string>
#include <vector>
#include <netinet/in.h>

using namespace std;
struct UserData
{
    string username; // store user data;
    string password; // store user password;
};

class UserManager
{
public:
    void loadUserFile(); // This function is used to load the data from the user_credential file  (user.txt)

    void saveUserFile(); //  This function save the data to user_credential file  (User.txt)

    /* authenticateUser(onst string &username, const string &password) : Authenticate the user by verify password and username
       argument1 :- Username of the user
       argument2 :- Password of the user */
    bool authenticateUser(const string &username, const string &password);


    /* isUsernameTaken(const string &username): Is username taken verify that if the user is already taken by existing user or not 
       argument1:- Username of the user
    */
    bool isUsernameTaken(const string &username);
};

// vector <UserData> user_data;

#endif // USER_MANAGER_H