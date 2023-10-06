// user_auth.h
#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <string>
#include <vector>
#include <netinet/in.h>

using namespace std;
struct UserData
{
    string username;
    string password;
};

class UserManager
{
public:

    void loadUserFile();   // This function is used to load the data from the user_credential file  (user.txt)
    void saveUserFile();   //  This function save the data to user_credential file  (User.txt)
    bool authenticateUser(const string &username, const string &password);
    bool isUsernameTaken(const string &username);

};

// vector <UserData> user_data;

#endif // USER_MANAGER_H