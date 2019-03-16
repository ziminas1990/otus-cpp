#include <map>
#include <iostream>

#include "Allocator.h"
#include "SimpleList.h"

// Why I can use inheritance, but can't use "using"?
//template<typename T>
//using awesome_allocator_8 = awesome_allocator<T, 8>;
template<typename T>
class dummy_allocator_8 : public dummy_allocator<T, 8>
{};

int main(int, char*[])
{
  std::map<int, int> defaultMap;
  for (int key = 0, value = 0; key < 10; ++key, value *= key) {
    defaultMap[key] = value;
    if (!key)
      value = 1;
  }

  std::map<int, int, std::less<int>, dummy_allocator_8<int>> awesomeMap;
  for (int key = 0, value = 0; key < 10; ++key, value *= key) {
    awesomeMap[key] = value;
    if (!key)
      value = 1;
  }

  for (auto const & node : awesomeMap) {
    std::cout << node.first << " " << node.second << std::endl;
  }

  SimpleList<int, dummy_allocator_8<int>> defaultList;
  for (int index = 0; index < 10; ++index) {
    defaultList.push_back(index);
  }

  SimpleList<int, dummy_allocator_8<int>> awesomeList;
  for (int index = 0; index < 10; ++index) {
    awesomeList.push_back(index);
  }
  for (auto const & value : awesomeList) {
    std::cout << value << std::endl;
  }
  return 0;
}
