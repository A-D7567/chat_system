//user_auth.cpp
#include <iostream>
#include <fstream>
#include <algorithm>
#include "server.h"
#include "user_auth.h"
#include <vector>

using namespace std;

void loadUserFile()
{
    ifstream userFile("users.txt");
    if (!userFile.is_open())
    {
        cout << "Error opening user file." << endl;
        return;
    }
    UserData user;
    while (userFile >> user.username >> user.password)
    {
        user_data.push_back(user);
    }
    userFile.close();

}

void saveUserFile()
{
    ofstream userFile("users.txt");
    if (!userFile.is_open())
    {
        cout << "Error opening user file." << endl;
        return;
    }
    for (const UserData &user : user_data)
    {
        userFile << "User_Name : " << user.username << "  Password : " << user.password << endl;
    }
    userFile.close();
}

bool authenticateUser(const std::string &username, const std::string &password)
{
    for (const UserData &user : user_data)
    {
        if (user.username == username && user.password == password)
        {
            return true; // Authentication successful
        }
    }
    return false; // Authentication failed
}

bool isUsernameTaken(const std::string &username)
{
    for (const UserData &user : user_data)
    {
        if (user.username == username)
        {
            return true; // Username is already taken
        }
    }
    return false; // Username is available
}