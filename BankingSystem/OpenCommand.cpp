#include "Commands/OpenCommand.h"
#include "IdGenerator.h"

#pragma warning(disable : 4996)

OpenCommand::OpenCommand(const SharedPtr<User> &accountHolder, const MyString &bankName)
    : accountHolder(accountHolder), bankName(bankName)
{
}

void OpenCommand::execute()
{
    unsigned newId = IdGenerator::getInstance().getUniqueId();

    System::getInstance().getBank(bankName).addAccount(BankAccount(newId, 0.f, accountHolder));
    char buff[15];
    MyString messege("You opened an account in " + bankName + "!" + "Your account id is " + itoa(newId, buff, 10));

    accountHolder->addMessage(messege);
}

void OpenCommand::cancel()
{
    char buff[1024]{0};
    std::cin.getline(buff, 1024);
    accountHolder->addMessage("Your Open request for bank " + bankName + "was not approved.  Reason: " + buff + ".");
}

void OpenCommand::view() const
{
    std::cout << "Open - " << accountHolder->getName() << " wants to create an account.\n";
}

void OpenCommand::details() const
{
    std::cout << "Open request from: \n";
    accountHolder->display();
}

Command *OpenCommand::clone() const
{
    return new OpenCommand(*this);
}
