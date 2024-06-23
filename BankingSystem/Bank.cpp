#include "Bank.h"
#include "Users/Employee.h"

Bank::Bank(const MyString &name) : name(name)
{
}

const MyString &Bank::getName() const
{
    return name;
}

const BankAccount &Bank::getBankAccount(unsigned id) const
{
    size_t count = accounts.size();
    if (!count)
        throw std::logic_error("There aren't any bank accounts");

    for (size_t i = 1; i < count; i++)
    {
        if (accounts[i].getId() == id)
            return accounts[i];
    }
    throw std::logic_error("not found");
}

BankAccount &Bank::getBankAccount(unsigned id)
{
    size_t count = accounts.size();

    if (!count)
        throw std::logic_error("There aren't any bank accounts");

    for (size_t i = 0; i < count; i++)
    {
        if (accounts[i].getId() == id)
            return accounts[i];
    }

    throw std::logic_error("no account with such id");
}

SharedPtr<Employee> &Bank::getEmployeeWithLeastTasks() const
{
    size_t count = employees.size();

    if (!count)
        throw std::runtime_error("no employees in that bank, can't procces this task");

    SharedPtr<Employee> res = employees[0];
    for (size_t i = 0; i < count; i++)
    {
        if (employees[i]->getWaitingTasksCount() < res->getWaitingTasksCount())
            res = employees[i];
    }

    return res;
}

void Bank::addAccount(const BankAccount &toAdd)
{
    accounts.push_back(toAdd);
}

const BankAccount &Bank::extractAccount(unsigned id)
{
    size_t count = accounts.size();

    if (!count)
        throw std::logic_error("There aren't any bankaccounts");

    BankAccount res;
    for (size_t i = 0; i < count; i++)
    {
        if (accounts[i].getId() == id)
        {
            res = accounts[i];
            accounts.erase(i);
        }
    }
    if (res.getId() == 0)
        throw std::logic_error("no account with such id");
    return res;
}

const MyVector<BankAccount> &Bank::getAccounts() const
{
    return accounts;
}

void Bank::addEmployee(const SharedPtr<Employee> &em)
{
    employees.push_back(em);
}
