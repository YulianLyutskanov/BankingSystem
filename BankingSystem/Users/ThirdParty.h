#pragma once
#include "Containers/MyVector.hpp"
#include "MyString.h"
#include "Users/User.h"
class ThirdParty : public User
{
  public:
    void exit() const override;
    void help() const override;
    void serialise(std::ostream &os) const override;

    UserType getType() const override;
    ThirdParty(const MyString &name, const MyString &id, unsigned short age, const MyString &password);
    ThirdParty(std::istream &is);

    void send_check(double sum, const MyString &verificationCode, const MyString &userId) const;

  private:
};
