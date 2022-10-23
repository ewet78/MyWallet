#include "Income.h"

int Income::getIncomeId(){
    return incomeId;
}

int Income::getUserId(){
    return userId;
}

int Income::getDate(){
    return date;
}

string Income::getItem(){
    return item;
}

string Income::getAmount(){
    return amount;
}

void Income::setIncomeId(int newIncomeId){
    incomeId = newIncomeId;
}

void Income::setUserId(int newUserId){
    userId = newUserId;
}

void Income::setDate(int newDate){
    date = newDate;
}

void Income::setItem(string newItem){
    item = newItem;
}

void Income::setAmount(string newAmount){
    amount = newAmount;
}
