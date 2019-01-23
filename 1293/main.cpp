#include <iostream>
#include <stdint.h>

int main()
{
  uint16_t N = 0;
  uint16_t A = 0;
  uint16_t B = 0;
  std::cin >> N >> A >> B;
  std::cout << (N * A * B * 2) << std::endl;
  return 0;
}
