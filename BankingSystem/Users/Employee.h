#pragma once
#include "../Commands/Command.h"
#include "../Containers/MyVector.hpp"
#include "../MyString.h"
#include "../SmartPointers/Polymorfic_Ptr.hpp"
#include "Users/User.h"

class Employee : public User
{
  public:
    void exit() const override;
    void help() const override;
    void serialise(std::ostream &os) const override;

    UserType getType() const override;

    void tasks() const;
    void view(unsigned taskId) const;
    void approve(unsigned taskId);
    void disapprove(unsigned taskId);
    unsigned getWaitingTasksCount() const;
    void addTask(Command *task);
    const MyString &getAssociatedBank() const;

    Employee(const MyString &name, const MyString &id, unsigned short age, const MyString &password,
             const MyString &bankAssociated);
    Employee(std::istream &is);

  private:
    MyString bankAssociated;
    MyVector<Polymorphic_Ptr<Command>> commands;
};
