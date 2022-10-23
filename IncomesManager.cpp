#include "IncomesManager.h"

int IncomesManager::getLastIncomeId(){
    return lastIncomeId;
}

void IncomesManager::addIncome() {
    Income income;
    char choice;
    string date;
    system("cls");
    cout << ">>> ADDING AN INCOME <<<" << endl << endl;
    cout << "Does an income is related to this day or would you like to choose another date?" << endl;
    cout << "Choose Y to this day or A to another date: ";
    cin >> choice;
    while (true) {
        if(choice=='Y'||choice=='y') {
            addIncomeToVectorAndFile(AuxiliaryMethods::convertStringToInt(loadCurrentDate()));
            cout << endl <<"Income has been added successfully" << endl;
            system ("pause");
            break;

        } else if (choice=='A'||choice=='a') {
            while (true) {
                cout << endl <<"Give date in format: yyyy-mm-dd" << endl;
                cin >> date;
                if (checkIfTheDateIsCorrect(date)>0) {
                    addIncomeToVectorAndFile(checkIfTheDateIsCorrect(date));
                    cout << endl <<"Income has been added successfully" << endl;
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

void IncomesManager::addIncomeToVectorAndFile(int date){
    Income income;
    string item;
    string amount;

    income.setDate(date);
    income.setIncomeId(getNewIncomeId());
    income.setUserId(ID_LOGGED_USER);
    cout << endl << "What was the income about? (e.g. salary, payout) " << endl;
    AuxiliaryMethods::readLine();
    item = AuxiliaryMethods::readLine();
    income.setItem(item);
    cout << endl << "What was the amount of income? " << endl;
    cin >> amount;
    income.setAmount(checkAmountOfIncome(amount));
    incomes.push_back(income);
    incomesFile.addIncomeToFile(income);
}

string IncomesManager::checkAmountOfIncome(string amount){
    for (int i=0; i<amount.size(); i++){
        if (amount[i]==','){
            amount[i]='.';
        }
        if (!isdigit(amount[i]) && amount[i]!='.' && amount[i]!=','){
            cout << "It is not amount. Try again. What was the amount of income? " <<endl;
            cin >> amount;
            i=0;
        }
    }

    return amount;

}

string IncomesManager::loadCurrentDate() {
    time_t rawtime;
    struct tm * timeinfo;
    string year;
    string month;
    string day;
    string date;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    year = AuxiliaryMethods::convertIntToString(1900+timeinfo->tm_year);

    month = AuxiliaryMethods::convertIntToString(timeinfo->tm_mon+1);
    if (month.size()==1)
        month='0'+month;

    day = AuxiliaryMethods::convertIntToString(timeinfo->tm_mday);
    if (day.size()==1)
        day='0'+day;

    date = year+month+day;
    return date;

}

int IncomesManager::checkIfTheDateIsCorrect(string date) {
    time_t rawtime;
    struct tm * timeinfo;
    string day = "";
    string month = "";
    string year = "";
    string dateWithoutDashes = "";

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    for (int i=0; i<date.size(); i++) {
        if (!isdigit(date[i]) && date[i] != '-'){
            return -1;
            }
        if(i<4 && date[i] != '-') {
            year += date[i];
        } if (i>4 && i<7 && date[i] != '-') {
            month += date[i];
        } if (i>7 && date[i] != '-') {
            day += date[i];
        }
    }
    if (AuxiliaryMethods::convertStringToInt(year)>=2000 && AuxiliaryMethods::convertStringToInt(year)<(1900+timeinfo->tm_year)) {
        if (AuxiliaryMethods::convertStringToInt(month)>=1 && AuxiliaryMethods::convertStringToInt(month)<=12 ) {
            if (AuxiliaryMethods::convertStringToInt(day)>=1 && AuxiliaryMethods::convertStringToInt(day)<=checkHowManyDaysHaveTheMonth(month, year)) {
                dateWithoutDashes = year+month+day;
            }
            if (AuxiliaryMethods::convertStringToInt(day)>checkHowManyDaysHaveTheMonth(month, year)) {
                    return 0;
            }
        }
        if (AuxiliaryMethods::convertStringToInt(month)>12) {
                return 0;
        }
    }
    if (AuxiliaryMethods::convertStringToInt(year) == (1900+timeinfo->tm_year)){
            if (AuxiliaryMethods::convertStringToInt(month)>=1 && AuxiliaryMethods::convertStringToInt(month)<timeinfo->tm_mon+1){
              if (AuxiliaryMethods::convertStringToInt(day)>=1 && AuxiliaryMethods::convertStringToInt(day)<=checkHowManyDaysHaveTheMonth(month, year)) {
                dateWithoutDashes = year+month+day;
                }
            }
            if (AuxiliaryMethods::convertStringToInt(month)==timeinfo->tm_mon+1){
                if (AuxiliaryMethods::convertStringToInt(day)>=1 && AuxiliaryMethods::convertStringToInt(day)<=checkHowManyDaysHaveTheMonth(month, year)){
                    dateWithoutDashes = year+month+day;
                }
            }
    }
    if (AuxiliaryMethods::convertStringToInt(year) > (1900+timeinfo->tm_year)) return 0;

    return AuxiliaryMethods::convertStringToInt(dateWithoutDashes);
}

int IncomesManager::checkHowManyDaysHaveTheMonth(string month, string year) {
    int daysOfTheMonth = 0;

    if (AuxiliaryMethods::convertStringToInt(month) == 4 || AuxiliaryMethods::convertStringToInt(month) == 6 || AuxiliaryMethods::convertStringToInt(month) == 9 || AuxiliaryMethods::convertStringToInt(month) == 11)
        daysOfTheMonth = 30;

    else if (AuxiliaryMethods::convertStringToInt(month) == 2) {
        bool leapyear = (AuxiliaryMethods::convertStringToInt(year) % 4 == 0 && AuxiliaryMethods::convertStringToInt(year) % 100 != 0) || (AuxiliaryMethods::convertStringToInt(year) % 400 == 0);

        if (leapyear == 0)
            daysOfTheMonth = 28;
        else
            daysOfTheMonth = 29;
    }

    else
        daysOfTheMonth = 31;

    return daysOfTheMonth;

}

int IncomesManager::getNewIncomeId() {
    int newIncomeId = incomesFile.getLastIncomeIdFromFile() + 1;
    return newIncomeId;
}

double IncomesManager::showIncomes(int date){
    double sumOfIncomes = 0;
    vector <Income> incomesToSort;

    if (!incomes.empty())
    {
        cout << "             >>> INCOMES <<<" << endl;
        cout << "-----------------------------------------------" << endl;
        for (vector <Income> :: iterator itr = incomes.begin(); itr != incomes.end(); itr++)
        {
            if (addIncomeToVectorToSort(*itr, date)){
                incomesToSort.push_back(*itr);
            }
        }

        sumOfIncomes += showDataOfSortedIncomes(incomesToSort, date);



        cout << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "Sum of incomes:                   ";
        printf(" %.2f\n", sumOfIncomes);
        cout << endl;
    }
    else
    {
        cout << endl << "There is no incomes." << endl << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "Sum of incomes:             " << sumOfIncomes << endl;
    }

    return sumOfIncomes;
}

bool IncomesManager::addIncomeToVectorToSort(Income income, int date){
    int dateWithCurrentMonth = date +100;
    if (income.getDate() > date && income.getDate() < dateWithCurrentMonth){
        return true;
    }
    return false;
}

double IncomesManager::showDataOfSortedIncomes (vector <Income> incomes, int date){
        double sumOfIncomes = 0;
        struct less_than_date
        {
        inline bool operator() (const Income& income1, const Income& income2)
        {
            return (income1.getDate() < income2.getDate());
        }
        };

        sort(incomes.begin(), incomes.end(), less_than_date());

        for (vector <Income> :: iterator itr = incomes.begin(); itr != incomes.end(); itr++)
        {
            sumOfIncomes += showDataOfIncome(*itr, date);
        }

        return sumOfIncomes;


}

double IncomesManager::showDataOfIncome(Income income, int date){
    double componentOfTheSum = 0;
    if (income.getDate() > date){
        cout << endl << "Id:                " << income.getIncomeId() << endl;

            string dateWithDashes = "";
            int dateWithoutDashes = income.getDate();
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
        cout << "Item:           " << income.getItem() << endl;
        cout << "Amount:         " << income.getAmount() << endl;
        componentOfTheSum = AuxiliaryMethods::convertStringToDouble(income.getAmount());
    }
    return componentOfTheSum;
}

double IncomesManager::showIncomesOfSelectedPeriod(int date1, int date2){
    double sumOfIncomes = 0;
    vector <Income> incomesToSort;

    if (!incomes.empty())
    {
        cout << "             >>> INCOMES <<<" << endl;
        cout << "-----------------------------------------------" << endl;
        for (vector <Income> :: iterator itr = incomes.begin(); itr != incomes.end(); itr++)
        {
            if (addIncomeOfSelectedPeriodToVectorToSort(*itr, date1, date2)){
                incomesToSort.push_back(*itr);
            }
        }

        sumOfIncomes += showDataOfSortedIncomesFromSelectedPeriod(incomesToSort, date1, date2);



        cout << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "Sum of incomes:                   ";
        printf(" %.2f\n", sumOfIncomes);
        cout << endl;
    }
    else
    {
        cout << endl << "There is no incomes." << endl << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "Sum of incomes:             " << sumOfIncomes << endl;
    }

    return sumOfIncomes;
}

bool IncomesManager::addIncomeOfSelectedPeriodToVectorToSort(Income income, int date1, int date2){
    string yearDate1 = "";
    string yearDate2 = "";
    string monthDate1 = "";
    string monthDate2 = "";
    string dayDate1 = "";
    string dayDate2 = "";

    string date1WithoutDashes = AuxiliaryMethods::convertIntToString(date1);
    string date2WithoutDashes = AuxiliaryMethods::convertIntToString(date2);

    int dateFromVectorInt = income.getDate();
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

double IncomesManager::showDataOfSortedIncomesFromSelectedPeriod (vector <Income> incomes, int date1, int date2){
        double sumOfIncomes = 0;
        struct less_than_date
        {
        inline bool operator() (const Income& income1, const Income& income2)
        {
            return (income1.getDate() < income2.getDate());
        }
        };

        sort(incomes.begin(), incomes.end(), less_than_date());

        for (vector <Income> :: iterator itr = incomes.begin(); itr != incomes.end(); itr++)
        {
            sumOfIncomes += showDataOfIncomeFromSelectedPeriod(*itr, date1, date2);
        }

        return sumOfIncomes;
}

double IncomesManager::showDataOfIncomeFromSelectedPeriod(Income income, int date1, int date2){
    double componentOfTheSum = 0;
    if (addIncomeOfSelectedPeriodToVectorToSort(income, date1, date2)){
        cout << endl << "Id:                " << income.getIncomeId() << endl;

            string dateWithDashes = "";
            int dateWithoutDashes = income.getDate();
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
        cout << "Item:           " << income.getItem() << endl;
        cout << "Amount:         " << income.getAmount() << endl;
        componentOfTheSum = AuxiliaryMethods::convertStringToDouble(income.getAmount());
    }
    return componentOfTheSum;
}
