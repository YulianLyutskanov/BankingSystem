#pragma once
#include "MyString.h"
class Check
{
  public:
    double getSum() const;
    const MyString &getCode() const;
    const MyString &getUserId() const;
    void serialise(std::ostream &os) const;

    Check(const MyString &sender, double sum, const MyString &verificationCode, const MyString &userId);
    Check() = default;
    Check(std::istream &is);

  private:
    MyString sender;
    double sum = 0;
    MyString verificationCode;
    MyString userId;
};
