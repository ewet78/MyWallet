#ifndef MYWALLET_H
#define MYWALLET_H

#include <iostream>

#include "UserManager.h"

using namespace std;

class MyWallet{
    UserManager userManager;

public:
    MyWallet(string usersFileName) : userManager(usersFileName){};
    void registerUser();
};



#endif
