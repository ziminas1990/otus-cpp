#include "lib.h"
#include <iostream>

int main (int argc, char *argv[])
{
    std::cout << "Hellow, world!\n" <<
                 "Version: " << version_major() << "." << version_minor() <<
                 ", build #" << version_patch() << std::endl;
    return 0;
}
