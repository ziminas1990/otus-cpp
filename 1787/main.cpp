#include <iostream>
#include <stdint.h>

int main()
{
  int nCarsPerMinute    = 0;
  int nTotalMinutes     = 0;
  int nTrafficJamLength = 0;
  std::cin >> nCarsPerMinute >> nTotalMinutes;
  for(int i = 0; i < nTotalMinutes; i++) {
    int nAdditionalCars = 0;
    std::cin >> nAdditionalCars;
    nTrafficJamLength += nAdditionalCars - nCarsPerMinute;
    if (nTrafficJamLength < 0)
      nTrafficJamLength = 0;
  }
  std::cout << nTrafficJamLength << std::endl;
  return 0;
}
