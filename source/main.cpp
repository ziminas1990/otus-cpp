#include "lib.h"
#include <iostream>
#include <string.h>

int main (int argc, char *argv[])
{
  std::cout << "Hellow, world!" << std::endl;

  if (argc == 2 && !strcmp(argv[1], "-v")) {
    std::cout << "Version: " << version_major() << "." << version_minor() <<
                 ", build #" << version_patch() << std::endl;
  }
  return 0;
}
