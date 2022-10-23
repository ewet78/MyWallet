#ifndef MYWALLET_H
#define MYWALLET_H

#include <iostream>

#include "UserManager.h"
#include "IncomesManager.h"
#include "IncomesFile.h"
#include "ExpensesManager.h"

using namespace std;

class MyWallet{
    UserManager userManager;
    IncomesManager *incomesManager;
    ExpensesManager *expensesManager;
    IncomesFile incomesFile;
    ExpensesFile expensesFile;

public:
    MyWallet(string usersFileName, string incomesFileName, string expensesFileName) : userManager(usersFileName), incomesFile(incomesFileName), expensesFile(expensesFileName){
        incomesManager = NULL;
        expensesManager = NULL;
    };
    ~MyWallet(){
        delete incomesManager;
        delete expensesManager;
        incomesManager = NULL;
        expensesManager = NULL;
    }
    bool isUserLoggedIn();
    void registerUser();
    void loggingUser();
    void logoutUser();
    void changePasswordOfLoggedUser();
    void addNewIncome();
    void addNewExpense();
    void showBalanceSheetForTheCurrentMonth();
    void showBalanceSheetForThePreviousMonth();
    void showBalanceSheetForTheSelectedPeriod();
};



#endif
