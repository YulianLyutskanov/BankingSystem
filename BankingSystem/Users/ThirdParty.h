#pragma once
#include "Containers/MyVector.hpp"
#include "MyString.h"
#include "Users/User.h"
class ThirdParty : public User
{
  public:
    void exit() const override;
    void help() const override;

    UserType getType() const override;

    void send_check(double sum, const MyString &verificationCode, const MyString &userId) const;

  private:
};