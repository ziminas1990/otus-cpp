#include <iostream>
#include <stdint.h>
#include <vector>
#include <string>

int main()
{
  using NamingConvention      = std::pair<uint16_t, std::string>;
  using NamingConventionTable = std::vector<NamingConvention>;
  NamingConventionTable table =
  {
    {1000, "legion"},
    {500,  "zounds"},
    {250,  "swarm"},
    {100,  "throng"},
    {50,   "horde"},
    {20,   "lots"},
    {10,   "pack"},
    {5,    "several"},
    {1,    "few"}
  };

  uint16_t total = 0;
  std::cin >> total;
  for (auto const& convention : table) {
    if (total >= convention.first) {
      std::cout << convention.second << std::endl;
      break;
    }
  }
  return 0;
}
