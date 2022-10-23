#include "ExpensesManager.h"

int ExpensesManager::getLastExpenseId(){
    return lastExpenseId;
}

void ExpensesManager::addExpense() {
    Expense expense;
    char choice;
    string date;
    system("cls");
    cout << ">>> ADDING AN EXPENSE <<<" << endl << endl;
    cout << "Does an expense is related to this day or would you like to choose another date?" << endl;
    cout << "Choose Y to this day or A to another date: ";
    cin >> choice;
    while (true) {
        if(choice=='Y'||choice=='y') {
            addExpenseToVectorAndFile(AuxiliaryMethods::convertStringToInt(loadCurrentDate()));
            cout << endl <<"Expense has been added successfully" << endl;
            system ("pause");
            break;

        } else if (choice=='A'||choice=='a') {
            while (true) {
                cout << endl <<"Give date in format: yyyy-mm-dd" << endl;
                cin >> date;
                if (checkIfTheDateIsCorrect(date)>0) {
                    addExpenseToVectorAndFile(checkIfTheDateIsCorrect(date));
                    cout << endl <<"Expense has been added successfully" << endl;
                    system ("pause");
                    break;
                }
                if (checkIfTheDateIsCorrect(date)==0){
                    cout << "Incorrect date. Try again.";
                }
                if (checkIfTheDateIsCorrect(date) < 0){
                    cout << endl << "Incorrect format of the date. Try again.";
                }
            }
            break;

        } else {
            cout <<endl << "Wrong choice. Try again (Y/A): ";
            cin >> choice;
        }
    }
}

void ExpensesManager::addExpenseToVectorAndFile(int date){
    Expense expense;
    string item;
    string amount;

    expense.setDate(date);
    expense.setExpenseId(getNewExpenseId());
    expense.setUserId(ID_LOGGED_USER);
    cout << endl << "What was the expense about? (e.g. shopping, rent) " << endl;
    AuxiliaryMethods::readLine();
    item = AuxiliaryMethods::readLine();
    expense.setItem(item);
    cout << endl << "What was the amount of expense? " << endl;
    cin >> amount;
    expense.setAmount(checkAmountOfExpense(amount));
    expenses.push_back(expense);
    expensesFile.addExpenseToFile(expense);
}

string ExpensesManager::checkAmountOfExpense(string amount){
    for (int i=0; i<amount.size(); i++){
        if (amount[i]==','){
            amount[i]='.';
        }
        if (!isdigit(amount[i]) && amount[i]!='.' && amount[i]!=','){
            cout << "It is not amount. Try again. What was the amount of expense? " <<endl;
            cin >> amount;
            i=0;
        }
    }

    return amount;

}


int ExpensesManager::getNewExpenseId() {
    int newExpenseId = expensesFile.getLastExpenseIdFromFile() + 1;
    return newExpenseId;
}

double ExpensesManager::showExpenses(int date){

    double sumOfExpenses = 0;
    vector <Expense> expensesToSort;

    if (!expenses.empty())
    {
        cout << endl <<"             >>> EXPENSES <<<" << endl;
        cout << "-----------------------------------------------" << endl;
        for (vector <Expense> :: iterator itr = expenses.begin(); itr != expenses.end(); itr++)
        {
            if(addExpenseToVectorToSort(*itr, date)){
                expensesToSort.push_back(*itr);
            }
        }

        sumOfExpenses += showDataOfSortedExpenses(expensesToSort, date);

        cout << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "Sum of expenses:                   ";
        printf(" %.2f\n", sumOfExpenses);
        cout << endl;
    }
    else
    {
        cout << endl << "There is no expenses." << endl << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "Sum of expenses:             " << sumOfExpenses << endl;
    }

    return sumOfExpenses;
}
bool ExpensesManager::addExpenseToVectorToSort(Expense expense, int date){
    int dateWithCurrentMonth = date +100;
    if (expense.getDate() > date && expense.getDate() < dateWithCurrentMonth){
        return true;
    }
    return false;
}

double ExpensesManager::showDataOfSortedExpenses (vector <Expense> expenses, int date){
        double sumOfExpenses = 0;
        struct less_than_date
        {
        inline bool operator() (const Expense& expense1, const Expense& expense2)
        {
            return (expense1.getDate() < expense2.getDate());
        }
        };

        sort(expenses.begin(), expenses.end(), less_than_date());

        for (vector <Expense> :: iterator itr = expenses.begin(); itr != expenses.end(); itr++)
        {
            sumOfExpenses += showDataOfExpense(*itr, date);
        }

        return sumOfExpenses;


}

double ExpensesManager::showDataOfExpense(Expense expense, int date){

    double componentOfTheSum = 0;
    if (expense.getDate() > date){
        cout << endl << "Id:                " << expense.getExpenseId() << endl;

            string dateWithDashes = "";
            int dateWithoutDashes = expense.getDate();
            string dateWithoutDashesString = AuxiliaryMethods::convertIntToString(dateWithoutDashes);
            for (int i=0; i<dateWithoutDashesString.size(); i++){

                dateWithDashes += dateWithoutDashesString[i];
                if (i==3){
                    dateWithDashes += "-";
                }
                if (i==5){
                    dateWithDashes += "-";
                }
            }

        cout << "Date:           " << dateWithDashes << endl;
        cout << "Item:           " << expense.getItem() << endl;
        cout << "Amount:         " << expense.getAmount() << endl;
        componentOfTheSum = AuxiliaryMethods::convertStringToDouble(expense.getAmount());
    }

    return componentOfTheSum;
}
double ExpensesManager::showExpensesOfSelectedPeriod(int date1, int date2){
    double sumOfExpenses = 0;
    vector <Expense> expensesToSort;

    if (!expenses.empty())
    {
        cout << "             >>> EXPENSES <<<" << endl;
        cout << "-----------------------------------------------" << endl;
        for (vector <Expense> :: iterator itr = expenses.begin(); itr != expenses.end(); itr++)
        {
            if (addExpenseOfSelectedPeriodToVectorToSort(*itr, date1, date2)){
                expensesToSort.push_back(*itr);
            }
        }

        sumOfExpenses += showDataOfSortedExpensesFromSelectedPeriod(expensesToSort, date1, date2);



        cout << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "Sum of expenses:                   ";
        printf(" %.2f\n", sumOfExpenses);
        cout << endl;
    }
    else
    {
        cout << endl << "There is no expenses." << endl << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "Sum of expenses:             " << sumOfExpenses << endl;
    }

    return sumOfExpenses;
}

bool ExpensesManager::addExpenseOfSelectedPeriodToVectorToSort(Expense expense, int date1, int date2){
    string yearDate1 = "";
    string yearDate2 = "";
    string monthDate1 = "";
    string monthDate2 = "";
    string dayDate1 = "";
    string dayDate2 = "";

    string date1WithoutDashes = AuxiliaryMethods::convertIntToString(date1);
    string date2WithoutDashes = AuxiliaryMethods::convertIntToString(date2);

    int dateFromVectorInt = expense.getDate();
    string dateFromVector = AuxiliaryMethods::convertIntToString(dateFromVectorInt);
    string yearFromVector = "";
    string monthFromVector = "";
    string dayFromVector = "";

    for (int i=0; i<date1WithoutDashes.size(); i++)
    {
        if(i<=3){
            yearDate1 += date1WithoutDashes[i];
            yearDate2 += date2WithoutDashes[i];
            yearFromVector += dateFromVector[i];
        }
        if(i>=4 && i <=5){
            monthDate1 += date1WithoutDashes[i];
            monthDate2 += date2WithoutDashes[i];
            monthFromVector += dateFromVector[i];
        }
        if (i>=6 && i<=7){
            dayDate1 += date1WithoutDashes[i];
            dayDate2 += date2WithoutDashes[i];
            dayFromVector += dayFromVector[i];
        }
    }

    int yearFromVectorInt = AuxiliaryMethods::convertStringToInt(yearFromVector);
    int yearDate1Int = AuxiliaryMethods::convertStringToInt(yearDate1);
    int yearDate2Int = AuxiliaryMethods::convertStringToInt(yearDate2);

    int monthFromVectorInt = AuxiliaryMethods::convertStringToInt(monthFromVector);
    int monthDate1Int = AuxiliaryMethods::convertStringToInt(monthDate1);
    int monthDate2Int = AuxiliaryMethods::convertStringToInt(monthDate2);

    int dayFromVectorInt = AuxiliaryMethods::convertStringToInt(yearFromVector);
    int dayDate1Int = AuxiliaryMethods::convertStringToInt(dayDate1);
    int dayDate2Int = AuxiliaryMethods::convertStringToInt(dayDate2);


    if (yearFromVectorInt>yearDate1Int && yearFromVectorInt < yearDate2Int){
        return true;
    }
    if (yearFromVectorInt == yearDate1Int){
        if (monthFromVectorInt >= monthDate1Int){
            return true;
        }
    }
    if (yearFromVectorInt == yearDate2Int){
        if (monthFromVectorInt < monthDate2Int){
            return true;
        }
        if (monthFromVectorInt == monthDate2Int){
            if (dayFromVectorInt <= dayDate2Int){
                return true;
            }
        }
    }
    else return false;
}

double ExpensesManager::showDataOfSortedExpensesFromSelectedPeriod (vector <Expense> expenses, int date1, int date2){
        double sumOfExpenses = 0;
        struct less_than_date
        {
        inline bool operator() (const Expense& expense1, const Expense& expense2)
        {
            return (expense1.getDate() < expense2.getDate());
        }
        };

        sort(expenses.begin(), expenses.end(), less_than_date());

        for (vector <Expense> :: iterator itr = expenses.begin(); itr != expenses.end(); itr++)
        {
            sumOfExpenses += showDataOfExpenseFromSelectedPeriod(*itr, date1, date2);
        }

        return sumOfExpenses;
}

double ExpensesManager::showDataOfExpenseFromSelectedPeriod(Expense expense, int date1, int date2){
    double componentOfTheSum = 0;
    if (addExpenseOfSelectedPeriodToVectorToSort(expense, date1, date2)){
        cout << endl << "Id:                " << expense.getExpenseId() << endl;

            string dateWithDashes = "";
            int dateWithoutDashes = expense.getDate();
            string dateWithoutDashesString = AuxiliaryMethods::convertIntToString(dateWithoutDashes);
            for (int i=0; i<dateWithoutDashesString.size(); i++){

                dateWithDashes += dateWithoutDashesString[i];
                if (i==3){
                    dateWithDashes += "-";
                }
                if (i==5){
                    dateWithDashes += "-";
                }
            }

        cout << "Date:           " << dateWithDashes << endl;
        cout << "Item:           " << expense.getItem() << endl;
        cout << "Amount:         " << expense.getAmount() << endl;
        componentOfTheSum = AuxiliaryMethods::convertStringToDouble(expense.getAmount());
    }
    return componentOfTheSum;
}
