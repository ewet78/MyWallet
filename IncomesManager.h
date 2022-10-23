#ifndef INCOMES_MANAGER_H
#define INCOMES_MANAGER_H

#include <iostream>
#include <vector>
#include <time.h>

#include "Income.h"
#include "IncomesFile.h"

using namespace std;

class IncomesManager{
    const int ID_LOGGED_USER;
    int lastIncomeId;
    vector <Income> incomes;
    IncomesFile incomesFile;


public:
    IncomesManager(string incomesFileName, int idLoggedUser) : incomesFile(incomesFileName), ID_LOGGED_USER(idLoggedUser){
        incomes = incomesFile.loadIncomesFromFile(ID_LOGGED_USER);
    }
    int getLastIncomeId();
    void addIncome();
    void addIncomeToVectorAndFile(int date);
    string loadCurrentDate();
    int checkIfTheDateIsCorrect(string date);
    int checkHowManyDaysHaveTheMonth(string month, string year);
    int getNewIncomeId();
    string checkAmountOfIncome(string amount);
    bool addIncomeToVectorToSort(Income income, int date);
    double showDataOfSortedIncomes (vector <Income> incomes, int date);
    double showIncomes(int date);
    double showDataOfIncome(Income income, int date);
    double showIncomesOfSelectedPeriod(int date1, int date2);
    bool addIncomeOfSelectedPeriodToVectorToSort(Income income, int date1, int date2);
    double showDataOfSortedIncomesFromSelectedPeriod (vector <Income> incomes, int date1, int date2);
    double showDataOfIncomeFromSelectedPeriod(Income income, int date1, int date2);





};

#endif
