#include "IdGenerator.h"
#include <iostream>
#include <stdexcept>

unsigned IdGenerator::getUniqueId()
{

    curId++;
    if (curId > (1 << 30))
        throw ::std::logic_error("Too many bank accounts created, no more unique ids");
    return curId;
}

void IdGenerator::setStartingId(unsigned newStarting)
{
    curId = newStarting;
}

IdGenerator &IdGenerator::getInstance()
{
    static IdGenerator instance;
    return instance;
}
