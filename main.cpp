#include <iostream>

#include "MyWallet.h"

using namespace std;

int main()
{
    MyWallet myWallet("users.xml");
    myWallet.registerUser();
    myWallet.loggingUser();
    myWallet.changePasswordOfLoggedUser();

    cout << "Hello world!" << endl;
    return 0;
}
