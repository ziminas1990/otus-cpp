#include <map>
#include <iostream>

#include "Allocator.h"
#include "SimpleVector.h"

// Why I can use inheritance, but can't use "using"?
//template<typename T>
//using awesome_allocator_16 = awesome_allocator<T, 16>;
template<typename T>
class dummy_allocator_16 : public dummy_allocator<T, 16>
{};

int main(int, char*[])
{
  std::map<int, int> defaultMap;
  for (int key = 0, value = 0; key < 10; ++key, value *= key) {
    defaultMap[key] = value;
    if (!key)
      value = 1;
  }

  std::map<int, int, std::less<int>, dummy_allocator_16<int>> awesomeMap;
  for (int key = 0, value = 0; key < 10; ++key, value *= key) {
    awesomeMap[key] = value;
    if (!key)
      value = 1;
  }

  for (auto const & node : awesomeMap) {
    std::cout << node.first << " " << node.second << std::endl;
  }
  return 0;
}
