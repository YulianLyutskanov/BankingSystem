#include "Users/Employee.h"

unsigned Employee::getWaitingTasksCount() const
{
    return commands.size();
}

void Employee::addTask(Command* task)
{
    commands.push_back(Polymorphic_Ptr<Command>(task));
        
}

Employee::Employee(const MyString &name, const MyString &id, unsigned short age, const MyString &password,
                   const MyString &bankAssociated)
    : User(name, id, age, password), bankAssociated(bankAssociated)
{
}

void Employee::exit() const
{
    System::getInstance().changeLogged(nullptr);
}

void Employee::help() const
{
}

UserType Employee::getType() const
{
    return UserType::EMPLOYEE;
}

void Employee::tasks() const
{
    size_t count = commands.size();
    if (!count)
    {
        std::cout << "No active tasks!\n";
        return;
    }

    for (size_t i = 0; i < count; i++)
    {
        std::cout << '[' << i << "] ";
        commands[i]->view();
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Employee::view(unsigned taskId) const
{
    commands[taskId]->details();
}

void Employee::approve(unsigned taskId)
{
    commands[taskId]->execute();
    commands.erase(taskId);
}

void Employee::disapprove(unsigned taskId)
{
    commands[taskId]->cancel();
    commands.erase(taskId);
}
