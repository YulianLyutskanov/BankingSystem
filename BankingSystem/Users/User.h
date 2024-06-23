#pragma once
// #include "../System.h"
#include "Containers/MyVector.hpp"
#include "MyString.h"
#include <iostream>
// class System;

enum class UserType
{
    CLIENT,
    EMPLOYEE,
    THIRD_PARTY
};

class User
{
    friend class System;

  public:
    virtual void exit() const = 0;
    virtual void whoami() const;
    virtual void help() const = 0;

    void display() const;

    virtual void printMessages() const;

    User(const MyString &name, const MyString &id, unsigned short age);

    const MyString &getName() const;
    const MyString &getId() const;
    const unsigned short getAge() const;

    void setName(const MyString &newName);
    void setId(const MyString &newId);
    void setAge(unsigned short newAge);

    void addMessage(const MyString &newMes);

    User(const MyString &name, const MyString &id, unsigned short age, const MyString &password);
    virtual ~User() = default;
    //{
    //    std::cout << "delted user " << getName() << std::endl;
    //}
    virtual UserType getType() const = 0;

  protected:
    MyString name;
    MyString id;
    unsigned short age = 0;
    MyString password;
    MyVector<MyString> messages;

    const MyString &getPassword() const;
};
