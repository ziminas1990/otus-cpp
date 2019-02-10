#include <iostream>
#include <stdint.h>

int main()
{
  int nFirstCode = 0;
  int nSecondCode = 0;
  std::cin >> nFirstCode >> nSecondCode;

  std::cout << ((nFirstCode % 2 == 0 || nSecondCode % 2 == 1) ? "yes" : "no") << std::endl;
  return 0;
}
