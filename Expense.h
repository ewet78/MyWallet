#ifndef EXPENSE_H
#define EXPENSE_H

#include <iostream>

#include "Income.h"

using namespace std;

class Expense : public Income{
    int expenseId;
    int userId;
    int date;
    string item;
    string amount;

public:
    int getExpenseId();

    void setExpenseId(int newExpenseId);
};

#endif
