#pragma once
#include "../SmartPointers/SharedPtr.hpp"
#include "../Users/User.h"
#include "Command.h"


class OpenCommand : public Command
{
  public:
    OpenCommand(const SharedPtr<User> &accountHolder, const MyString &bankName);
    void execute() override;
    void cancel() override;
    void view() const override;
    void details() const override;
    Command *clone() const override;

  private:
    SharedPtr<User> accountHolder;
    MyString bankName;
};
