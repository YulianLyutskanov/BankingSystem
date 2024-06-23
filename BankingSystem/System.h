#pragma once
#include "Bank.h"
#include "Check.h"
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

    System(const System &other) = delete;
    System &operator=(const System &other) = delete;

    void addBank(const MyString &name);
    void addUser(User *user);

    Bank &getBank(const MyString &name);
    bool bankExists(const MyString &name);
    SharedPtr<User> &getUser(const MyString &id);
    bool isSomeoneLogged() const;
    void addCheck(const Check &check);
    const Check &findCheck(const MyString &code);

    void run();

  private:
    MyVector<Bank> banks;
    MyVector<SharedPtr<User>> users;
    MyVector<Check> checks;
    SharedPtr<User> loggedUser = nullptr;

    void changeLogged(SharedPtr<User> toLog);
    void extractCheck(const MyString &code);
    void singUp();
    void login();
    void clientInterface(const MyString &input);
    void employeeInterface(const MyString &input);
    void thirdPartyInterface(const MyString &input);
    bool commonUserInterface(const MyString &input);
    bool manageCommand(const MyString &input);

    bool isClientIdUnique(const MyString &input);

    System() = default;
};
