//user_auth.h
#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <string>
#include <vector>
#include "server.h"
#include "user_auth.h"

struct UserData
{
    std::string username;
    std::string password;
};

//std::vector <UserData> user_data;

void loadUserFile();
void saveUserFile();
bool authenticateUser(const std::string &username, const std::string &password);
bool isUsernameTaken(const std::string &username);

#endif // USER_MANAGER_H