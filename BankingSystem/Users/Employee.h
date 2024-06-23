#pragma once
#include "../Commands/Command.h"
#include "../Containers/MyVector.hpp"
#include "../MyString.h"
#include "../SmartPointers/Polymorfic_Ptr.hpp"
#include "../System.h"
#include "Users/User.h"

class Employee : public User
{
  public:
    void exit() const override;
    void help() const override;

    UserType getType() const override;

    void tasks() const;
    void view(unsigned taskId) const;
    void approve(unsigned taskId);
    void disapprove(unsigned taskId);
    // void validate(unsigned taskId) const;
    unsigned getWaitingTasksCount() const;
    void addTask(Command *task);

    Employee(const MyString &name, const MyString &id, unsigned short age, const MyString &password,
             const MyString &bankAssociated);
    //~Employee()
    //{
    //    std::cout << "deleted Employee " << getName() << std::endl;
    //}

  private:
    const MyString bankAssociated;
    MyVector<Polymorphic_Ptr<Command>> commands;
};
