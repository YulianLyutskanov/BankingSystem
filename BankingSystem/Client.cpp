#include "Users/Client.h"

void Client::exit() const
{
    System::getInstance().changeLogged(nullptr);
}

void Client::help() const
{
    std::cout << "check_avl [bank_name] [account_number] - Check balance on account\n";
    std::cout << "open [bank_name] - Open new savings account in a bank\n";
    std::cout << "close [bank_name] [account_number] - Close an existing acount of yours\n";
    std::cout << "redeem [bank_name] [account_number] [verification_code] - todo\n";
    std::cout << "change [new_bank_name] [current_bank_name] [account_number] - Transfer the account in another bank\n";
    std::cout << "list [bank_name] - View all of your available saving accounts in this bank\n";
    std::cout << "messages - Displays all messages in chronological order\n";
    std::cout << "exit - logout\n";
}

UserType Client::getType() const
{
    return UserType::CLIENT;
}

void Client::check_avl(const MyString &bankName, unsigned accountNumber) const
{
    std::cout << System::getInstance().getBank(bankName).getBankAccount(accountNumber).getBalance() << '$' << std::endl;
}

void Client::list(const MyString &bankName) const
{
    size_t count = System::getInstance().getBank(bankName).getAccounts().size();

    for (size_t i = 0; i < count; i++)
    {
        BankAccount cur = System::getInstance().getBank(bankName).getAccounts()[i];
        if (cur.getUser()->getName() == name)
            std::cout << cur.getId() << std::endl;
    }
}

Client::Client(const MyString &name, const MyString &id, unsigned short age, const MyString &password)
    : User(name, id, age, password)
{
}