#pragma once
#include "../SmartPointers/SharedPtr.hpp"
#include "../Users/User.h"
#include "Command.h"

class ChangeCommand : public Command
{
  public:
    ChangeCommand(const SharedPtr<User> &accountHolder, const MyString &destinationBank, const MyString &initialBank,
                  unsigned accountId);
    void execute() override;
    void cancel() override;
    void view() const override;
    void details() const override;
    Command *clone() const override;

  private:
    SharedPtr<User> accountHolder;
    MyString destinationBank;
    MyString initialBank;
    unsigned accountId;
};
