#pragma once
#include "SmartPointers/SharedPtr.hpp"
#include "Users/User.h"
class BankAccount
{
  public:
    BankAccount(unsigned id, double balance, SharedPtr<User> user);
    BankAccount() = default;

    unsigned getId() const;
    double getBalance() const;
    const SharedPtr<User> &getUser() const;

    void setId(unsigned newId);
    void setBalance(double newBalance);
    void add(double money);
    void setUser(User *newUser);
    void print() const;

  private:
    unsigned id = 0;
    double balance = 0.f;
    SharedPtr<User> user;
};
