#pragma once
#include "BankAccount.h"
#include "Containers/MyVector.hpp"
#include "Users/User.h"
class Employee;
class Bank
{
  public:
    Bank(const MyString &name);
    Bank() = default;
    Bank(std::istream &is);
    const MyString &getName() const;
    const BankAccount &getBankAccount(unsigned id) const;
    BankAccount &getBankAccount(unsigned id);
    SharedPtr<Employee> &getEmployeeWithLeastTasks() const;

    void addAccount(const BankAccount &toAdd);
    const BankAccount &extractAccount(unsigned id);
    const MyVector<BankAccount> &getAccounts() const;
    void addEmployee(const SharedPtr<Employee> &em);
    void serialise(std::ostream &os) const;

  private:
    MyString name;
    MyVector<BankAccount> accounts;
    MyVector<SharedPtr<Employee>> employees;
};
