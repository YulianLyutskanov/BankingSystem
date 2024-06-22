#include "System.h"
#include "Commands/ChangeCommand.h"
#include "Commands/CloseCommand.h"
#include "Commands/OpenCommand.h"
#include "Users/Employee.h"
#include "Users/ThirdParty.h"

System &System::getInstance()
{
    static System instance;
    return instance;
}

void System::addBank(const MyString &name)
{
    // check if it exists
    banks.push_back(name);
}

void System::addUser(User *user)
{
    users.push_back(SharedPtr<User>(user));
}

Bank &System::getBank(const MyString &name)
{
    size_t count = banks.size();

    if (!count)
        throw std::logic_error("no banks yet!");

    for (size_t i = 0; i < count; i++)
    {
        if (banks[i].getName() == name)
            return banks[i];
    }

    throw std::logic_error("bank now found");
}

SharedPtr<User> &System::getUser(const MyString &id)
{
    size_t count = users.size();

    if (!count)
        throw std::logic_error("no users yet!");

    for (size_t i = 0; i < count; i++)
    {
        if (users[i]->getId() == id)
            return users[i];
    }
    throw std::logic_error("user now found");
}

bool System::isSomeoneLogged() const
{
    return loggedUser.isInitlized();
    ;
}

void System::addCheck(const Check &check)
{
    checks.push_back(check);
}

const Check &System::findCheck(const MyString &code)
{
    size_t count = checks.size();
    // if(!count)

    for (size_t i = 0; i < count; i++)
    {
        if (checks[i].getCode() == code)
            return checks[i];
    }
}

void System::extractCheck(const MyString &code)
{
    size_t count = checks.size();
    // if(!count)

    for (size_t i = 0; i < count; i++)
    {
        if (checks[i].getCode() == code)
            checks.erase(i);
    }
}

void System::run()
{
    while (true)
    {
        if (!isSomeoneLogged())
        {
            MyString input;
            std::cin >> input;
            if (input == "create_bank")
            {
                std::cin >> input;
                addBank(input);
                std::cout << std::endl;
            }
            else if (input == "signup")
            {
                SharedPtr<User> newUser;

                MyString name, id, role, password;
                unsigned age = 0;
                std::cout << "Name: ";
                std::cin >> name;
                std::cout << std::endl << "EGN: ";
                std::cin >> id;
                std::cout << std::endl << "Age: ";
                std::cin >> age;
                std::cout << std::endl << "Role: ";
                std::cin >> role;
                if (role == "Client")
                {
                    std::cout << std::endl << "Password: ";
                    std::cin >> password;
                    newUser = new Client(name, id, age, password);
                }
                else if (role == "Employee")
                {
                    MyString bank;
                    std::cout << "Bank associated: ";
                    std::cin >> bank;
                    std::cout << std::endl << "Password: ";
                    std::cin >> password;
                    newUser = new Employee(name, id, age, password, bank);
                    SharedPtr<Employee> employee(dynamicCast<Employee, User>(newUser));
                    getBank(bank).addEmployee(employee);
                }
                else if (role == "Third-Party")
                {
                    std::cout << std::endl << "Password: ";
                    std::cin >> password;
                    newUser = new ThirdParty(name, id, age, password);
                }
                users.push_back(newUser);
            }
            else if (input == "login")
            {
                MyString name, password;
                std::cout << "Name: ";
                std::cin >> name;
                std::cout << std::endl << "Password: ";
                std::cin >> password;

                size_t count = users.size();
                for (size_t i = 0; i < count; i++)
                {
                    if (users[i]->getName() == name && users[i]->getPassword() == password)
                    {
                        changeLogged(users[i]);
                    }
                }
            }
            else if (input == "exit")
            {
                return;
            }
        }
        else if (loggedUser->getType() == UserType::CLIENT)
        {
            MyString input;
            std::cin >> input;
            if (input == "check_avl")
            {
                MyString bankName;
                unsigned accountId;
                std::cin >> bankName >> accountId;
                dynamicCast<Client, User>(loggedUser)->check_avl(bankName, accountId);
            }
            else if (input == "list")
            {
                MyString bankName;
                std::cin >> bankName;
                dynamicCast<Client, User>(loggedUser)->list(bankName);
            }
            else if (input == "messages")
            {
                dynamicCast<Client, User>(loggedUser)->printMessages();
            }
            else if (input == "help")
            {
                dynamicCast<Client, User>(loggedUser)->help();
            }
            else if (input == "open")
            {
                MyString bankName;
                std::cin >> bankName;
                getBank(bankName).getEmployeeWithLeastTasks()->addTask(new OpenCommand(loggedUser, bankName));
            }
            else if (input == "close")
            {
                MyString bankName;
                unsigned accountNum;
                std::cin >> bankName >> accountNum;
                getBank(bankName).getEmployeeWithLeastTasks()->addTask(
                    new CloseCommand(loggedUser, bankName, accountNum));
            }
            else if (input == "redeem")
            {
                MyString bankName;
                unsigned accountNum;
                MyString verificationCode;
                std::cin >> bankName >> accountNum >> verificationCode;
                dynamicCast<Client, User>(loggedUser)->redeem(bankName, accountNum, verificationCode);
            }
            else if (input == "change")
            {
                MyString destBank, curBank;
                unsigned accNumber;
                std::cin >> destBank >> curBank >> accNumber;
                getBank(destBank).getEmployeeWithLeastTasks()->addTask(
                    new ChangeCommand(loggedUser, destBank, curBank, accNumber));
            }
            else if (input == "whoami")
            {
                loggedUser->whoami();
            }
            else if (input == "exit")
            {
                loggedUser->exit();
            }
        }
        else if (loggedUser->getType() == UserType::EMPLOYEE)
        {
            MyString input;
            std::cin >> input;
            if (input == "tasks")
            {
                dynamicCast<Employee, User>(loggedUser)->tasks();
            }
            else if (input == "view")
            {
                unsigned index;
                std::cin >> index;
                dynamicCast<Employee, User>(loggedUser)->view(index);
            }
            else if (input == "approve")
            {
                unsigned index;
                std::cin >> index;
                dynamicCast<Employee, User>(loggedUser)->approve(index);
            }
            else if (input == "disapprove")
            {
                unsigned index;
                std::cin >> index;
                dynamicCast<Employee, User>(loggedUser)->disapprove(index);
            }
            else if (input == "whoami")
            {
                loggedUser->whoami();
            }
            else if (input == "exit")
            {
                loggedUser->exit();
            }
        }
        else if (loggedUser->getType() == UserType::THIRD_PARTY)
        {
            MyString input;
            std::cin >> input;
            if (input == "whoami")
            {
                loggedUser->whoami();
            }
            else if (input == "help")
            {
                loggedUser->help();
            }
            else if (input == "send_check")
            {
                double sum;
                MyString code, egn;
                std::cin >> sum >> code >> egn;
                dynamicCast<ThirdParty, User>(loggedUser)->send_check(sum, code, egn);
            }
            else if (input == "exit")
            {
                loggedUser->exit();
            }
        }
    }
}

void System::changeLogged( SharedPtr<User> toLog)
{
    loggedUser = toLog;
}
