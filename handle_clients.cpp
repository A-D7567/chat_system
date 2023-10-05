#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <unistd.h>
#include "user_auth.h"
#include "handle_clients.h"

using namespace std;

extern vector<UserData> user_data;
UserManager local_user;

int Clienthandler::handel_signup()
{
    // Handle sign-up
    memset(buffer, 0, sizeof(buffer));
    int username_length = recv(client_socket, buffer, sizeof(buffer), 0);

    if (username_length <= 0)
    {
        cout << "Enter Valid Username.." << endl;
        close(client_socket);
        return 1;
    }

    string new_username(buffer, username_length);
    username = new_username; 
    // send(client_socket, "Enter a new password: ", strlen("Enter a new password: "), 0);
    memset(buffer, 0, sizeof(buffer));
    int password_length = recv(client_socket, buffer, sizeof(buffer), 0);

    if (password_length <= 0)
    {
        cout << "Enter valid Password.." << endl;
        close(client_socket);
        return 1;
    }

    string new_password(buffer, password_length);
    if (!local_user.isUsernameTaken(new_username))
    {
        UserData new_user;
        new_user.username = new_username;
        new_user.password = new_password;
        user_data.push_back(new_user);
        local_user.saveUserFile();
        send(client_socket, "Signup successful.", strlen("Signup successful."), 0);
        return 0;
    }
    else
    {
        cout << "username is already taken......." << endl;
        send(client_socket, "Username is already taken.......\n", strlen("Username is already taken.......t\n"), 0);
        close(client_socket);
        return 1;
    }

}

int Clienthandler::handel_login()
{   // Handle login
    // send(client_socket, "Enter username: ", strlen("Enter username: "), 0);

    memset(buffer, 0, sizeof(buffer));
    int username_length = recv(client_socket, buffer, sizeof(buffer), 0);
    if (username_length <= 0)
    {
        cout << "Enter Valid Username.." << endl;
        close(client_socket);
        return 1;
    }


    string client_username(buffer, username_length);
    // send(client_socket, "Enter password: ", strlen("Enter password: "), 0);
    memset(buffer, 0, sizeof(buffer));
    int password_length = recv(client_socket, buffer, sizeof(buffer), 0);

    if (password_length <= 0)
    {
        cout << "Enter valid Password.." << endl;
        close(client_socket);
        return 1;
    }


    string client_password(buffer, password_length);

    if (local_user.authenticateUser(client_username, client_password))
    {
        username = client_username;
        send(client_socket, "Authentication successful.", strlen("Authentication successful."), 0);
        return 0;
    }
    else
    {   send(client_socket, "Username or password is incorrect\n", strlen("Username or password is incorrect\n"), 0);
        send(client_socket, "Authentication failed. Try again.", strlen("Authentication failed. Try again."), 0);
        close(client_socket);
        return 1;
    }

}


void Clienthandler::handle_rec()
{
    char buffer[1024];

    while (1)
    {
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0)
        {
            close(client_socket);
            return;
        }
        
        // Add logic to process client messages here
        if (strcmp(buffer, "login") == 0)
        {
            // Handle login
            int error_code=0;
            error_code = handel_login();
            if(error_code == 1)
            {
                cout << "\nLogin failed \n\n";
                
                return;
            }
                cout <<"---------------------------------------------"<< endl;
                cout <<"\rA user have logged in as " << username  << endl;
                cout <<"---------------------------------------------"<< endl;
            
        }
        else if (strcmp(buffer, "signup") == 0){
    
            // Handle sign-up
            int error_code;
            error_code = handel_signup();

            if(error_code == 1)
            {
                cout << "\nRegistering a new user failed \n\n";
                return;
            }
            
            cout <<"-------------------------------------------"<< endl;
            cout <<"\rNew account has been created with username : " << username << endl;
            cout <<"-------------------------------------------"<< endl;
        }
        else
        {
            cout <<"\r" << username << " : " << buffer << " " << endl;
        }
        
        write(0,"\rServer : ", strlen("\rServer : "));
    }
}

void Clienthandler::handle_send()
{
    char buffer[1024];
    while (1)
    {
        
        cin.getline(buffer, sizeof(buffer));

        if (strcmp(buffer,"@exit") == 0)
        {
            send(client_socket, "@exit", strlen("@exit"), 0);

            close(client_socket);
            sleep(1);
            cout <<"The server program is closed \n";
            exit(0);
        }

        send(client_socket, buffer, strlen(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
        cout <<"Server : ";
    }
}

int Clienthandler::handle_client()
{

    char buffer[1024];
    cout << "-------------------------------------------" << "\n";
    cout << "A Client is trying to connect on FD : " << client_socket << "\n";
    cout << "-------------------------------------------" << "\n";

    thread rec( [this](){ handle_rec(); } );
    thread ([this](){ handle_send(); }).detach();
   
    rec.join();
    cout << "\nClient with fd is closed  : " << client_socket << "\n";

    return 0;   
}
