#include "Users/User.h"

void User::whoami() const
{
    display();
}

void User::display() const
{
    std::cout << "Name: " + name << std::endl << "EGN: " + id << std::endl << "Age: " << age << std::endl;
}

void User::printMessages() const
{
    size_t count = messages.size();
    if (!count)
    {
        std::cout << "There are no messages yet!\n";
        return;
    }

    for (size_t i = 0; i < count; i++)
    {
        std::cout << '[' << i << "] - " << messages[i] << std::endl;
    }
}

User::User(const MyString &name, const MyString &id, unsigned short age) : name(name), id(id), age(age)
{
}

const MyString &User::getName() const
{
    return name;
}

const MyString &User::getId() const
{
    return id;
}

const unsigned short User::getAge() const
{
    return age;
}

void User::setName(const MyString &newName)
{
    name = newName;
}

void User::setId(const MyString &newId)
{
    // check if it is unique
    id = newId;
}

void User::setAge(unsigned short newAge)
{
    age = newAge;
}

void User::addMessage(const MyString &newMes)
{
    messages.push_back(newMes);
}

User::User(const MyString &name, const MyString &id, unsigned short age, const MyString &password)
    : name(name), id(id), age(age), password(password)
{
}

const MyString &User::getPassword() const
{
    return password;
}
