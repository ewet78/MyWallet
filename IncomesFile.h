#ifndef INCOMESFILE_H
#define INCOMESFILE_H

#include <iostream>
#include <vector>

#include "Markup.h"
#include "Income.h"
#include "UsersFile.h"
#include "AuxiliaryMethods.h"

using namespace std;

class IncomesFile : public UsersFile {
    const string INCOMES_FILE_NAME;
    CMarkup xmlIncomes;
public:
    IncomesFile(string incomesFileName) : UsersFile(incomesFileName), INCOMES_FILE_NAME(incomesFileName) {};
    vector <Income> loadIncomesFromFile(int idLoggedUser);
    int getLastIncomeIdFromFile();
    void addIncomeToFile(Income income);
};

#endif
