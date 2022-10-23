#include "ExpensesFile.h"

vector <Expense> ExpensesFile::loadExpensesFromFile(int idLoggedUser){
    Expense expense;
    vector <Expense> expenses;
    int userIdFromXML = 0;
    int lastExpenseId = 0;

    if (xmlExpenses.Load(EXPENSES_FILE_NAME)) {
            xmlExpenses.FindElem();
            xmlExpenses.IntoElem();

            while(xmlExpenses.FindElem("Expense")){
                xmlExpenses.IntoElem();
                xmlExpenses.FindElem("ExpenseId");
                lastExpenseId = AuxiliaryMethods::convertStringToInt(xmlExpenses.GetData());
                xmlExpenses.FindElem("UserId");
                userIdFromXML = AuxiliaryMethods::convertStringToInt(xmlExpenses.GetData());

                if(userIdFromXML != idLoggedUser){
                    xmlExpenses.OutOfElem();
                    continue;
                }

                expense.setUserId(userIdFromXML);
                expense.setExpenseId(lastExpenseId);

                xmlExpenses.FindElem("Date");
                expense.setDate(AuxiliaryMethods::convertStringToInt(xmlExpenses.GetData()));
                xmlExpenses.FindElem("Item");
                expense.setItem(xmlExpenses.GetData());
                xmlExpenses.FindElem("Amount");
                expense.setAmount(xmlExpenses.GetData());
                xmlExpenses.OutOfElem();

                    expenses.push_back(expense);
                }

            }


    return expenses;
}

int ExpensesFile::getLastExpenseIdFromFile() {
    int lastExpenseId = 0;
    if (xmlExpenses.Load(EXPENSES_FILE_NAME)) {
        xmlExpenses.FindElem();
        xmlExpenses.IntoElem();

        while(xmlExpenses.FindElem("Expense")) {
            xmlExpenses.IntoElem();
            xmlExpenses.FindElem("ExpenseId");
            lastExpenseId = AuxiliaryMethods::convertStringToInt(xmlExpenses.GetData());
            xmlExpenses.OutOfElem();
        }
    }
     return lastExpenseId;
}

void ExpensesFile::addExpenseToFile(Expense expense){

    bool fileExist = xmlExpenses.Load(EXPENSES_FILE_NAME);

    if (!fileExist)
    {
        xmlExpenses.AddElem("Expenses");
    }

    xmlExpenses.FindElem();
    xmlExpenses.IntoElem();
    xmlExpenses.AddElem("Expense");
    xmlExpenses.IntoElem();
    xmlExpenses.AddElem("ExpenseId", expense.getExpenseId());
    xmlExpenses.AddElem("UserId", expense.getUserId());
    xmlExpenses.AddElem("Date", expense.getDate());
    xmlExpenses.AddElem("Item", expense.getItem());
    xmlExpenses.AddElem("Amount", expense.getAmount());

    xmlExpenses.Save(EXPENSES_FILE_NAME);

}
