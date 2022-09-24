#include <iostream>

#include "MyWallet.h"

using namespace std;

int main()
{
    MyWallet myWallet("users");
    myWallet.registerUser();

    cout << "Hello world!" << endl;
    return 0;
}
