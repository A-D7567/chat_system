//server.h
#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <netinet/in.h>

const int PORT = 3338;
const int MAX_CONNECTIONS = 5;
const int MAX_BUFFER_SIZE = 1024;

void saveUserFile();
bool authenticateUser(const std::string &username, const std::string &password);
bool isUsernameTaken(const std::string &username);
void handle_client(int client_socket);

#endif // SERVER_H