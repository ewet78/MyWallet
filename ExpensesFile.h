#ifndef EXPENSESFILE_H
#define EXPENSESFILE_H

#include <iostream>
#include <vector>

#include "Markup.h"
#include "Expense.h"
#include "UsersFile.h"
#include "AuxiliaryMethods.h"

using namespace std;

class ExpensesFile : public UsersFile {
    const string EXPENSES_FILE_NAME;
    CMarkup xmlExpenses;
public:
    ExpensesFile(string expensesFileName) : UsersFile(expensesFileName), EXPENSES_FILE_NAME(expensesFileName) {};
    vector <Expense> loadExpensesFromFile(int idLoggedUser);
    int getLastExpenseIdFromFile();
    void addExpenseToFile(Expense expense);
};

#endif
