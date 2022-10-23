#ifndef EXPENSES_MANAGER_H
#define EXPENSES_MANAGER_H

#include <iostream>
#include <vector>
#include <time.h>

#include "Expense.h"
#include "ExpensesFile.h"
#include "IncomesManager.h"

using namespace std;

class ExpensesManager :public IncomesManager{
    const int ID_LOGGED_USER;
    int lastExpenseId;
    vector <Expense> expenses;
    ExpensesFile expensesFile;
public:
    ExpensesManager(string expensesFileName, int idLoggedUser) : IncomesManager(expensesFileName, idLoggedUser), expensesFile(expensesFileName), ID_LOGGED_USER(idLoggedUser){
        expenses = expensesFile.loadExpensesFromFile(ID_LOGGED_USER);
    }
    int getLastExpenseId();
    void addExpense();
    void addExpenseToVectorAndFile(int date);
    int getNewExpenseId();
    string checkAmountOfExpense(string amount);
    bool addExpenseToVectorToSort(Expense expense, int date);
    double showDataOfSortedExpenses (vector <Expense> expenses, int date);
    double showExpenses(int date);
    double showDataOfExpense(Expense expense, int date);
    double showExpensesOfSelectedPeriod(int date1, int date2);
    bool addExpenseOfSelectedPeriodToVectorToSort(Expense expense, int date1, int date2);
    double showDataOfSortedExpensesFromSelectedPeriod (vector <Expense> expenses, int date1, int date2);
    double showDataOfExpenseFromSelectedPeriod(Expense expense, int date1, int date2);


};

#endif
