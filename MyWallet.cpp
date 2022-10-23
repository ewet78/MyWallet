#include "MyWallet.h"

void MyWallet::registerUser(){
    userManager.registerUser();
}

void MyWallet::loggingUser(){

    userManager.loggingUser();
    if (userManager.isUserLoggedIn())
    {
        incomesManager = new IncomesManager(incomesFile.getFileName(), userManager.getLoggedUserId());
        expensesManager = new ExpensesManager(expensesFile.getFileName(), userManager.getLoggedUserId());
    }
}

void MyWallet::changePasswordOfLoggedUser(){
    userManager.changePasswordOfLoggedUser(userManager.getLoggedUserId());
}

void MyWallet::addNewIncome(){
    incomesManager -> addIncome();
}

void MyWallet::addNewExpense(){
    expensesManager -> addExpense();
}

bool MyWallet::isUserLoggedIn(){
    userManager.isUserLoggedIn();
}
void MyWallet::logoutUser(){
   userManager.logoutUser();
}

void MyWallet::showBalanceSheetForTheCurrentMonth(){
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    string currentMonth = AuxiliaryMethods::convertIntToString(timeinfo->tm_mon+1);
    if (AuxiliaryMethods::convertStringToInt(currentMonth) < 10){
        currentMonth = "0" + currentMonth;
    }

    string currentYear = AuxiliaryMethods::convertIntToString(1900+timeinfo->tm_year);
    string currentDate = currentYear + currentMonth + "00";
    int currentDateInt = AuxiliaryMethods::convertStringToInt(currentDate);
    double balance = 0;

    system("cls");
    balance += incomesManager -> showIncomes(currentDateInt);
    balance -= expensesManager -> showExpenses(currentDateInt);

    cout << endl;
    cout << "..............................................." << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "BUDGET SUMMARY:             ";
    if (balance > 0){
        cout << "+ ";
    };

    cout << balance << endl;


    system("pause");
}

void MyWallet::showBalanceSheetForThePreviousMonth(){
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    string previousMonth = AuxiliaryMethods::convertIntToString(timeinfo->tm_mon);
    if (AuxiliaryMethods::convertStringToInt(previousMonth) < 10){
        previousMonth = "0" + previousMonth;
    }

    string currentYear = AuxiliaryMethods::convertIntToString(1900+timeinfo->tm_year);
    string date = currentYear + previousMonth + "00";
    int dateInt = AuxiliaryMethods::convertStringToInt(date);
    double balance = 0;

    system("cls");
    balance += incomesManager -> showIncomes(dateInt);
    balance -= expensesManager -> showExpenses(dateInt);

    cout << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "BUDGET SUMMARY:             ";
    if (balance > 0){
        cout << "+ ";
    };

    cout << balance << endl;


    system("pause");
}

void MyWallet::showBalanceSheetForTheSelectedPeriod(){

    string date1 = "";
    string date2 = "";
    system("cls");
    cout << "Give the date FROM WHEN to show the balance sheet: " << endl;
    cout << "Give date in format: yyyy-mm-dd" << endl;
    cin >> date1;
    while (true){
    if (incomesManager -> checkIfTheDateIsCorrect(date1) > 0){
        break;
    }
    if (incomesManager -> checkIfTheDateIsCorrect(date1) == 0){
                    cout <<endl << "Incorrect date. Try again."<<endl;
                    cin >> date1;

                }
    if (incomesManager -> checkIfTheDateIsCorrect(date1) < 0){
        cout << endl << "Incorrect format of the date. Try again."<<endl;
        cin >> date1;
    }
    }
    cout <<endl << "Give the date TO WHEN to show the balance sheet: " << endl;
    cout << "Give date in format: yyyy-mm-dd" << endl;
    cin >> date2;
    while (true){
    if (incomesManager -> checkIfTheDateIsCorrect(date2) > 0){
        break;
    }
    if (incomesManager -> checkIfTheDateIsCorrect(date2) == 0){
                    cout <<endl << "Incorrect date. Try again."<<endl;
                    cin >> date2;

                }
    if (incomesManager -> checkIfTheDateIsCorrect(date2) < 0){
        cout << endl << "Incorrect format of the date. Try again."<<endl;
        cin >> date2;
    }
    }

    int date1Int = AuxiliaryMethods::convertStringToInt(date1);
    int date2Int = AuxiliaryMethods::convertStringToInt(date2);
    double balance = 0;

    system("cls");
    balance += incomesManager -> showIncomesOfSelectedPeriod(date1Int, date2Int);
    balance -= expensesManager -> showExpensesOfSelectedPeriod(date1Int, date2Int);

    cout << endl;
    cout << "..............................................." << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "BUDGET SUMMARY:             ";
    if (balance > 0){
        cout << "+ ";
    };

    cout << balance << endl;


    system("pause");



}
