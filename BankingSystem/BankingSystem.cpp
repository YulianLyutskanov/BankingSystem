#include "System.h"

#include <iostream>

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // first line in main function

    System::getInstance().run();
    return 0;
}
