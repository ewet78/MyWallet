#include "IncomesFile.h"

vector <Income> IncomesFile::loadIncomesFromFile(int idLoggedUser){
    Income income;
    vector <Income> incomes;
    int userIdFromXML = 0;
    int lastIncomeId = 0;

    if (xmlIncomes.Load(INCOMES_FILE_NAME)) {
            xmlIncomes.FindElem();
            xmlIncomes.IntoElem();

            while(xmlIncomes.FindElem("Income")){
                xmlIncomes.IntoElem();
                xmlIncomes.FindElem("IncomeId");
                lastIncomeId = AuxiliaryMethods::convertStringToInt(xmlIncomes.GetData());
                xmlIncomes.FindElem("UserId");
                userIdFromXML = AuxiliaryMethods::convertStringToInt(xmlIncomes.GetData());

                if(userIdFromXML != idLoggedUser){
                    xmlIncomes.OutOfElem();
                    continue;
                }

                income.setUserId(userIdFromXML);
                income.setIncomeId(lastIncomeId);

                xmlIncomes.FindElem("Date");
                income.setDate(AuxiliaryMethods::convertStringToInt(xmlIncomes.GetData()));
                xmlIncomes.FindElem("Item");
                income.setItem(xmlIncomes.GetData());
                xmlIncomes.FindElem("Amount");
                income.setAmount(xmlIncomes.GetData());
                xmlIncomes.OutOfElem();

                    incomes.push_back(income);
                }

            }


    return incomes;
}

int IncomesFile::getLastIncomeIdFromFile() {
    int lastIncomeId = 0;
    if (xmlIncomes.Load(INCOMES_FILE_NAME)) {
        xmlIncomes.FindElem();
        xmlIncomes.IntoElem();

        while(xmlIncomes.FindElem("Income")) {
            xmlIncomes.IntoElem();
            xmlIncomes.FindElem("IncomeId");
            lastIncomeId = AuxiliaryMethods::convertStringToInt(xmlIncomes.GetData());
            xmlIncomes.OutOfElem();
        }
    }
     return lastIncomeId;
}

void IncomesFile::addIncomeToFile(Income income){

    bool fileExist = xmlIncomes.Load(INCOMES_FILE_NAME);

    if (!fileExist)
    {
        xmlIncomes.AddElem("Incomes");
    }

    xmlIncomes.FindElem();
    xmlIncomes.IntoElem();
    xmlIncomes.AddElem("Income");
    xmlIncomes.IntoElem();
    xmlIncomes.AddElem("IncomeId", income.getIncomeId());
    xmlIncomes.AddElem("UserId", income.getUserId());
    xmlIncomes.AddElem("Date", income.getDate());
    xmlIncomes.AddElem("Item", income.getItem());
    xmlIncomes.AddElem("Amount", income.getAmount());

    xmlIncomes.Save(INCOMES_FILE_NAME);

}
