#include <iostream>
#include <stdint.h>

int main()
{
  int n = 0;
  int k = 0;
  std::cin >> n >> k;
  if (n <= k) {
    std::cout << 2 << std::endl;
  } else {
    int nTotalSides = n * 2;
    std::cout << nTotalSides / k + (nTotalSides % k ? 1 : 0) << std::endl;
  }
  return 0;
}
