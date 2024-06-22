#pragma once
#include "Bank.h"
#include "Containers/MyVector.hpp"
#include "MyString.h"
#include "SmartPointers/Polymorfic_Ptr.hpp"
#include "SmartPointers/SharedPtr.hpp"
#include "Users/Client.h"
// #include "Users/Employee.h"
#include "Users/User.h"

class System
{
    friend class User;
    friend class Client;
    friend class Employee;
    friend class ThirdParty;

  public:
    static System &getInstance();

    System() = default;
    System(const System &other) = delete;
    System &operator=(const System &other) = delete;

    void addBank(const MyString &name);
    void addUser(User *user);

    Bank &getBank(const MyString &name);
    SharedPtr<User> &getUser(const MyString &id);
    bool isSomeoneLogged() const;

    void run();

  private:
    MyVector<Bank> banks;
    MyVector<SharedPtr<User>> users;
    SharedPtr<User> loggedUser = nullptr;

    void changeLogged(const SharedPtr<User> &toLog);
};
