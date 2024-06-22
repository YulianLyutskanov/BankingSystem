#pragma once
#include "../SmartPointers/SharedPtr.hpp"
#include "../Users/User.h"
#include "Command.h"

class CloseCommand : public Command
{
  public:
    CloseCommand(const SharedPtr<User> &accountHolder, const MyString &bankName, unsigned accountId);
    void execute() override;
    void cancel() override;
    void view() const override;
    void details() const override;
    Command *clone() const override;

  private:
    SharedPtr<User> accountHolder;
    MyString bankName;
    unsigned accountId;
};
