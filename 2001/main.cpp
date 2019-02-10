#include <iostream>
#include <stdint.h>

int main()
{
  int nFirstBacketTotal  = 0;
  int nSecondBacketTotal = 0;
  int nFirstBacketEmpty  = 0;
  int nSecondBacketEmpty = 0;
  int useless            = 0;
  std::cin >> nFirstBacketTotal >> nSecondBacketTotal;
  std::cin >> useless >> nSecondBacketEmpty;
  std::cin >> nFirstBacketEmpty >> useless;
  std::cout << (nFirstBacketTotal - nFirstBacketEmpty) << " " <<
               (nSecondBacketTotal - nSecondBacketEmpty) << std::endl;
  return 0;
}
