#include "BankAccount.h"
#include "System.h"

BankAccount::BankAccount(unsigned id, double balance, SharedPtr<User> user) : id(id), balance(balance), user(user)
{
}

BankAccount::BankAccount(std::istream &is)
{
    is >> id >> balance;
    MyString ownerID;
    is >> ownerID;
    user = System::getInstance().getUser(ownerID);
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
    id = newId;
}

void BankAccount::setBalance(double newBalance)
{
    balance = newBalance;
}

void BankAccount::add(double money)
{
    balance += money;
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

void BankAccount::serialise(std::ostream &os) const
{
    os << id << ' ' << balance << ' ' << user->getId();
}
