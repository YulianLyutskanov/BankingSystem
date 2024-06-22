#include "BankAccount.h"

BankAccount::BankAccount(unsigned id, double balance, SharedPtr<User> user) : id(id), balance(balance), user(user)
{
}

unsigned BankAccount::getId() const
{
    return id;
}

double BankAccount::getBalance() const
{
    return balance;
}

const SharedPtr<User> &BankAccount::getUser() const
{
    return user;
}

void BankAccount::setId(unsigned newId)
{
    // check if its free
    id = newId;
}

void BankAccount::setBalance(double newBalance)
{
    balance = newBalance;
}

void BankAccount::setUser(User *newUser)
{
    if (!newUser)
        throw std::invalid_argument("nullptr");
    user = newUser;
}

void BankAccount::print() const
{
    std::cout << "Account number: " << id << std::endl << "Balance: " << balance << '$' << std::endl;
}
