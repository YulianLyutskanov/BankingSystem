#pragma once
#include "../Containers/MyVector.hpp"
#include "../MyString.h"
#include "../System.h"
// #include "../Commands/Command.h"
#include "Users/User.h"
class Client : public User
{
  public:
    void exit() const override;
    void help() const override;

    UserType getType() const override;

    void check_avl(const MyString &bankName, unsigned accountNumber) const;
    // void open(const MyString &bankName) const;
    // void close(const MyString &bankName, unsigned accountNumber) const;
    // void redeem(const MyString &bankName, unsigned accountNumber, const MyString &verificationCode) const;
    // void change(const MyString &newBankName, const MyString &currentBankName, unsigned accountNumber) const;
    void list(const MyString &bankName) const;
    Client(const MyString &name, const MyString &id, unsigned short age, const MyString &password);

  private:
};
