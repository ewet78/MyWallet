#ifndef USERSFILE_H
#define USERSFILE_H

#include <iostream>
#include <vector>

#include "Markup.h"
#include "User.h"
#include "AuxiliaryMethods.h"

using namespace std;

class UsersFile{
    const string USERS_FILE_NAME;
    CMarkup xmlUsers;
public:
    UsersFile(string usersFileName) : USERS_FILE_NAME(usersFileName){};
    string getFileName();
    void addUserToFile(User user);
    vector <User> loadUsersFromFile();

    void changePasswordInXML(int userId, string newPassword);

};


#endif

