#include "Commands/ChangeCommand.h"
#pragma warning(disable : 4996)

ChangeCommand::ChangeCommand(const SharedPtr<User> &accountHolder, const MyString &destinationBank,
                             const MyString &initialBank, unsigned accountId)
    : accountHolder(accountHolder), destinationBank(destinationBank), initialBank(initialBank), accountId(accountId)
{
}

void ChangeCommand::execute()
{
    // check if the client has an existing account with this number
    try
    {
        BankAccount test = System::getInstance().getBank(initialBank).getBankAccount(accountId);
    }
    catch (std::logic_error &e)
    {
        std::cerr << e.what();
        accountHolder->addMessage("Change failed! The given account data were not valid!");
    }
    BankAccount cur = System::getInstance().getBank(initialBank).extractAccount(accountId);
    cur.setId(/*random num*/ 5);
    System::getInstance().getBank(destinationBank).addAccount(cur);
    char buff[15];
    accountHolder->addMessage("You changed your savings account to" + destinationBank + ". New account id is " +
                              itoa(/*random num*/ 5, buff, 10) + ".");
}

void ChangeCommand::cancel()
{
    char buff[1024]{0};
    char buff2[15]{0};
    std::cin.getline(buff, 1024);
    accountHolder->addMessage("Your Change request from bank " + initialBank + " to bank " + destinationBank +
                              " for account with id " + itoa(accountId, buff2, 10) +
                              "was not approved.  Reason: " + buff);
}

void ChangeCommand::view() const
{
    std::cout << "Change - " << accountHolder->getName() << " wants to join " << destinationBank << '.' << std::endl;
}

void ChangeCommand::details() const
{
    std::cout << "Change request from: \n";
    accountHolder->display();
    std::cout << "Bank: " << initialBank << std::endl;
}

Command* ChangeCommand::clone() const
{
    return  new ChangeCommand(*this);
}
