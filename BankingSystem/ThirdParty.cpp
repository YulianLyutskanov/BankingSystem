#include "Users/ThirdParty.h"
#include "System.h"

void ThirdParty::exit() const
{
    System::getInstance().changeLogged(nullptr);
}

void ThirdParty::help() const
{
    std::cout << "send_check [sum] [verification_code] [egn]" << std::endl;
    std::cout << "whoami - Display your information" << std::endl;
    std::cout << "exit - logout" << std::endl;
}

void ThirdParty::serialise(std::ostream &os) const
{
    os << name << '\n' << id << '\n' << age << '\n' << password << '\n';
}

UserType ThirdParty::getType() const
{
    return UserType::THIRD_PARTY;
}

ThirdParty::ThirdParty(const MyString &name, const MyString &id, unsigned short age, const MyString &password)
    : User(name, id, age, password)
{
}

ThirdParty::ThirdParty(std::istream& is)
{
    is >> name >> id >> age >> password;
}

void ThirdParty::send_check(double sum, const MyString &verificationCode, const MyString &userId) const
{

    System::getInstance().getUser(userId)->addMessage("You have a check assigned to you by " + getName());
    System::getInstance().addCheck(Check(getName(), sum, verificationCode, userId));
}
