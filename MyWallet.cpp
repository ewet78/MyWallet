#include "MyWallet.h"

void MyWallet::registerUser(){

    userManager.registerUser();
}

void MyWallet::loggingUser(){

    userManager.loggingUser();
}

void MyWallet::changePasswordOfLoggedUser(){

    userManager.changePasswordOfLoggedUser(userManager.getLoggedUserId());
}
