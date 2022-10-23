#include <iostream>

#include "MyWallet.h"

using namespace std;

int main() {
    MyWallet myWallet("users.xml", "incomes.xml", "expenses.xml");
    char choice;
    while (true) {
        if (!myWallet.isUserLoggedIn()) {
            system("cls");
            cout << "    >>> MAIN MENU <<<" << endl;
            cout << "---------------------------" << endl;
            cout << "1. Registration" << endl;
            cout << "2. Logging" << endl;
            cout << "9. Exit" << endl;
            cout << "---------------------------" << endl;
            cout << "Your choice: ";
            cin >> choice;

            switch (choice) {
            case '1':
                myWallet.registerUser();
                break;
            case '2':
                myWallet.loggingUser();
                break;
            case '9':
                exit(0);
                break;
            default:
                cout << endl << "There is not such option in menu." << endl << endl;
                system("pause");
                break;
            }
        } else {
            system("cls");
            cout << ">>>>>>>>>>>>>>>> USER MENU <<<<<<<<<<<<<<<<<<" << endl;
            cout << "---------------------------------------------" << endl;
            cout << "1. Add income" << endl;
            cout << "2. Add expense" << endl;
            cout << "3. Show balance sheet for the current month" << endl;
            cout << "4. Show balance sheet for the previous month" << endl;
            cout << "5. Show balance sheet for the selected period" << endl;
            cout << "---------------------------------------------" << endl;
            cout << "6. Change password" << endl;
            cout << "7. Log out" << endl;
            cout << "---------------------------------------------" << endl;
            cout << "Your choice: ";
            cin >> choice;

            switch (choice) {
            case '1':
                myWallet.addNewIncome();
                break;
            case '2':
                myWallet.addNewExpense();
                break;
            case '3':
                myWallet.showBalanceSheetForTheCurrentMonth();
                break;
            case '4':
                myWallet.showBalanceSheetForThePreviousMonth();
                break;
            case '5':
                myWallet.showBalanceSheetForTheSelectedPeriod();
                break;
            case '6':
                myWallet.changePasswordOfLoggedUser();
                break;
            case '7':
                myWallet.logoutUser();
                break;

            default:
                cout << endl << "There is not such option in menu." << endl << endl;
                system("pause");
                break;
            }
        }

    }

    return 0;
}
