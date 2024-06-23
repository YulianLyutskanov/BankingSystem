#include "Check.h"

double Check::getSum() const
{
    return sum;
}

const MyString &Check::getCode() const
{
    return verificationCode;
}

const MyString &Check::getUserId() const
{
    return userId;
}

void Check::serialise(std::ostream &os) const
{
    os << sender << ' ' << sum << ' ' << verificationCode << ' ' << userId;
}

Check::Check(const MyString &sender, double sum, const MyString &verificationCode, const MyString &userId)
    : sender(sender), sum(sum), verificationCode(verificationCode), userId(userId)
{
}

Check::Check(std::istream& is)
{
    is >> sender >> sum >> verificationCode >> userId;
}
