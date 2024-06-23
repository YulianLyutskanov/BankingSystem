#pragma once
#include "Bank.h"
#include "Check.h"
#include "Containers/MyVector.hpp"
#include "MyString.h"
#include "SmartPointers/SharedPtr.hpp"
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
    bool clientWithNameExists(const MyString &name);

    void run();

    ~System();

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

    void countUsersByType(size_t &clientsCount, size_t &employeesCount, size_t &thirdPartyCount) const;

    void serialiseUsers() const;
    void serialiseChecks() const;
    void serialiseBanks() const;
    // void serialiseLoggedUser() const; the deafult state of the program will be withoiut logged user
    void serialise() const;

    void loadUsers();
    void loadChecks();
    void loadBanks();

    void loadSystem();

    System();
};
