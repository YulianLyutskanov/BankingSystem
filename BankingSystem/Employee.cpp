#include "Users/Employee.h"

unsigned Employee::getWaitingTasksCount() const
{
    return commands.size();
}

void Employee::addTask(Command *task)
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
    std::cout << "tasks - shows your tasks" << std::endl;
    std::cout << "view [task_id] - shows details on the task by index " << std::endl;
    std::cout << "approve [task_id]" << std::endl;
    std::cout << "disapprove [task_id] [message]" << std::endl;
    std::cout << "whoami - Display your information" << std::endl;
    std::cout << "exit - logout" << std::endl;
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
    if (taskId >= commands.size())
        throw std::invalid_argument("no task with that index");
    commands[taskId]->details();
}

void Employee::approve(unsigned taskId)
{

    if (taskId >= commands.size())
        throw std::invalid_argument("no task with that index");
    commands[taskId]->execute();
    commands.erase(taskId);
}

void Employee::disapprove(unsigned taskId)
{
    if (taskId >= commands.size())
        throw std::invalid_argument("no task with that index");
    commands[taskId]->cancel();
    commands.erase(taskId);
}
