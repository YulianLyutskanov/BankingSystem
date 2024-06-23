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
    if (bankExists(name))
        throw std::logic_error("bank already exists!");

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

bool System::bankExists(const MyString &name)
{
    size_t count = banks.size();

    for (size_t i = 0; i < count; i++)
    {
        if (banks[i].getName() == name)
            return true;
    }
    return false;
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
}

void System::addCheck(const Check &check)
{
    checks.push_back(check);
}

const Check &System::findCheck(const MyString &code)
{
    size_t count = checks.size();

    for (size_t i = 0; i < count; i++)
    {
        if (checks[i].getCode() == code)
            return checks[i];
    }

    throw std::logic_error("no such a check!");
}

void System::extractCheck(const MyString &code)
{
    size_t count = checks.size();

    for (size_t i = 0; i < count; i++)
    {
        if (checks[i].getCode() == code)
        {
            checks.erase(i);
            return;
        }
    }

    throw std::logic_error("no such a check!");
}

void System::run()
{
    while (true)
    {
        MyString input;
        std::cin >> input;

        try
        {
            bool shouldExit = manageCommand(input);
            if (shouldExit)
                return;
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}

void System::changeLogged(SharedPtr<User> toLog)
{
    loggedUser = toLog;
}

void System::singUp()
{
    SharedPtr<User> newUser;

    MyString name, id, role, password;
    unsigned age = 0;
    std::cout << "Name: ";
    std::cin >> name;
    std::cout << std::endl << "EGN: ";
    std::cin >> id;

    if (!isClientIdUnique(id))
        throw std::logic_error("client with this id already exists!");

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

        if (!bankExists(bank))
            throw std::logic_error("this bank does not exist!");

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

void System::login()
{
    MyString name, password;
    std::cout << "Name: ";
    std::cin >> name;
    std::cout << std::endl << "Password: ";
    std::cin >> password;

    size_t count = users.size();
    for (size_t i = 0; i < count; i++)
    {
        if (users[i]->getName() == name) // find the user
        {
            if (users[i]->getPassword() == password)
            { // check the password
                changeLogged(users[i]);
                return;
            }
            else
                throw std::logic_error("Wrong password!");
        }
    }
    throw std::logic_error("no user with that name!");
}

void System::clientInterface(const MyString &input)
{
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
        getBank(bankName).getEmployeeWithLeastTasks()->addTask(new CloseCommand(loggedUser, bankName, accountNum));
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
}

void System::employeeInterface(const MyString &input)
{
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
}

void System::thirdPartyInterface(const MyString &input)
{
    if (input == "send_check")
    {
        double sum;
        MyString code, egn;
        std::cin >> sum >> code >> egn;
        dynamicCast<ThirdParty, User>(loggedUser)->send_check(sum, code, egn);
    }
}

bool System::commonUserInterface(const MyString &input)
{
    if (input == "help") // common user logic
    {
        loggedUser->help();
        return true;
    }
    else if (input == "whoami")
    {
        loggedUser->whoami();
        return true;
    }
    else if (input == "exit")
    {
        loggedUser->exit();
        return true;
    }
    return false;
}

bool System::manageCommand(const MyString &input)
{
    if (!isSomeoneLogged())
    {
        if (input == "create_bank")
        {
            MyString bankName;
            std::cin >> bankName;
            addBank(bankName);
            std::cout << std::endl;
        }
        else if (input == "signup")
        {
            singUp();
        }
        else if (input == "login")
        {
            login();
        }
        else if (input == "exit")
        {
            return true;
        }
    }
    else
    {
        if (commonUserInterface(input))
        {
            // logic is in the method ^
        }
        else if (loggedUser->getType() == UserType::CLIENT)
        {
            clientInterface(input);
        }
        else if (loggedUser->getType() == UserType::EMPLOYEE)
        {
            employeeInterface(input);
        }
        else if (loggedUser->getType() == UserType::THIRD_PARTY)
        {
            thirdPartyInterface(input);
        }
    }
    return false;
}

bool System::isClientIdUnique(const MyString &input)
{
    size_t count = users.size();

    for (size_t i = 0; i < count; i++)
    {
        if (users[i]->getId() == input)
            return false;
    }
    return true;
}
