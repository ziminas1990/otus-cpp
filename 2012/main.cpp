#include <iostream>
#include <stdint.h>

int main()
{
  uint16_t f = 0;
  std::cin >> f;
  std::cout << (f > 6 ? "YES" : "NO") << std::endl;
  return 0;
}
