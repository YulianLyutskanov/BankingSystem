#pragma once
#include "../Containers/MyVector.hpp"
#include "../MyString.h"
#include "Users/User.h"

class Client : public User
{
  public:
    void exit() const override;
    void help() const override;

    UserType getType() const override;

    void check_avl(const MyString &bankName, unsigned accountNumber) const;
    void redeem(const MyString &bankName, unsigned accountNumber, const MyString &verificationCode) const;
    void list(const MyString &bankName) const;
    Client(const MyString &name, const MyString &id, unsigned short age, const MyString &password);

  private:
};
