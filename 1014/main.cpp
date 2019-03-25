#include <iostream>
#include <stdint.h>
#include <array>

int64_t justDoIt(int N)
{
  int64_t Q = 0;
  uint64_t position = 1;
  while (N != 1) {
    int figure = 9;
    while(N % figure && figure > 1)
      --figure;
    if (figure == 1)
      return -1;
    Q        += figure * position;
    position *= 10;
    N        /= figure;
  }
  return Q;
}

int main()
{
  int N = 0;
  std::cin >> N;

  if (N == 0) {
    std::cout << 10 << std::endl;
  } else if (N <= 9) {
    std::cout << N << std::endl;
  } else {
    std::cout << justDoIt(N) << std::endl;
  }
  return 0;
}
