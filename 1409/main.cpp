#include <iostream>
#include <stdint.h>

int main()
{
  int nGarryShots;
  int nLarryShots;
  std::cin >> nGarryShots >> nLarryShots;
  std::cout << (nLarryShots - 1) << " " << (nGarryShots - 1) << std::endl;
  return 0;
}
