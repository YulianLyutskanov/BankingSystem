#include "Commands/CloseCommand.h"
#include "System.h"
#pragma warning(disable : 4996)

CloseCommand::CloseCommand(const SharedPtr<User> &accountHolder, const MyString &bankName, unsigned accountId)
    : accountHolder(accountHolder), bankName(bankName), accountId(accountId)
{
}

void CloseCommand::execute()
{
    // must fix to not let delete account that is not ours
    System::getInstance().getBank(bankName).extractAccount(accountId);
    char buff[15];
    MyString messege("You closed your account in " + bankName + "! Your account id was " + itoa(accountId, buff, 10));
    accountHolder->addMessage(messege);
}

void CloseCommand::cancel()
{
    char buff[1024]{0};
    char buff2[15];
    std::cin.getline(buff, 1024);
    accountHolder->addMessage("Your Close request for bank " + bankName + " for account with Id " +
                              itoa(accountId, buff2, 10) + " was not approved.  Reason: " + buff + ".");
}

void CloseCommand::view() const
{
    std::cout << "Close - " << accountHolder->getName() << " wants to close account  with id " << accountId << '.'
              << std::endl;
}

void CloseCommand::details() const
{
    std::cout << "Close request from: \n";
    accountHolder->display();
    std::cout << "Bank: " << bankName << std::endl;
    System::getInstance().getBank(bankName).getBankAccount(accountId).print();
}

Command *CloseCommand::clone() const
{
    return new CloseCommand(*this);
}
