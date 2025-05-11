#include "Deposit.h"
#include <iostream>
#include <exception>
#include "../../menu/MyException.h"


Deposit::Deposit(const std::string& name, double amount, double rate) 
    : name(name), amount(amount), interestRate(rate) {}

std::ostream& operator<<(std::ostream& os, const Deposit& dep) {
    os << "Вклад: " << dep.name 
       << "\nСумма: " << dep.amount 
       << "\nПроцент: " << dep.interestRate << "%";
    return os;
}

std::istream& operator>>(std::istream& is, Deposit& dep) {
    std::cout << "Название вклада: ";
    is >> dep.name;
    std::cout << "Сумма: ";
    is >> dep.amount;
    if(is.fail() || dep.amount < 0) throw MyException("Сумма должна быть положительной!");
    std::cout << "Процентная ставка (%): ";
    is >> dep.interestRate;
    if(is.fail() || dep.interestRate < 0 || dep.interestRate > 100) throw MyException("Процент некорректен!");
    return is;
}

std::string Deposit::getName() const { 
    return name; 
}

double Deposit::getAmount() const { 
    return amount; 
}

double Deposit::getInterestRate() const { 
    return interestRate; 
}