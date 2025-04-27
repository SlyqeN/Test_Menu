#include "Client.h"
#include <iostream>

Client::Client(const std::string& login, const std::string& password) {
    this->login = login;
    this->password = password;
}

bool Client::addDeposit(const Deposit& deposit) {
    if (deposits.getSize() < 10) {
        deposits.push_back(deposit);
        return true;
    }
    return false;
}

bool Client::operator==(const Client& other) const {
    return login == other.login;
}

bool Client::operator<(const Client& other) const {
    return login < other.login;
}

const Deposit* Client::getDeposits() const {
    return deposits.data();
}

int Client::getDepositCount() const {
    return deposits.getSize();
}

std::ostream& operator<<(std::ostream& os, const Client& client) {
    os << "Клиент: " << client.login << "\nВклады: " << client.deposits.getSize();
    return os;
}

std::istream& operator>>(std::istream& is, Client& client) {
    std::cout << "Введите логин: ";
    is >> client.login;
    std::cout << "Введите пароль: ";
    is >> client.password;
    return is;
}

void Client::displayInfo() const {
    std::cout << *this << "\n";
}