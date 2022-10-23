#include "AuxiliaryMethods.h"


static string AuxiliaryMethods::convertIntToString(int number)
{
    ostringstream ss;
    ss << number;
    string str = ss.str();
    return str;
}


static int AuxiliaryMethods::convertStringToInt(string number)
{
    int numberInt;
    istringstream iss(number);
    iss >> numberInt;

    return numberInt;
}

static string AuxiliaryMethods::readLine()
{
    string input = "";
    getline(cin, input);
    return input;
}

static double AuxiliaryMethods::convertStringToDouble(string amount){
    double number = stod(amount);
    return number;
}
