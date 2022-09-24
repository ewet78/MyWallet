#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <iostream>
#include <vector>

#include "User.h"
#include "UsersFile.h"

using namespace std;

class UserManager {
    int idLoggedUser;
    vector <User> users;

    User giveNewUserData();
    int getNewUserId();
    bool isLoginExist(string login);

    UsersFile usersFile;

public:
    UserManager(string usersFileName) : usersFile(usersFileName){
        idLoggedUser = 0;
        users = usersFile.loadUsersFromFile();
    }
    int getLoggedUserId();
    void setLoggedUserId(int newId);
    bool isUserLoggedIn();
    void registerUser();
    void loggingUser();
    void logoutUser();
    void changePasswordOfLoggedUser(int idLoggedUser);
};






#endif
