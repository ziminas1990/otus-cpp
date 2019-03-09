#include <iostream>
#include <stdint.h>
#include <vector>
#include <algorithm>

void inputNumbers(std::vector<int>& numbers)
{
  size_t nTotal;
  std::cin >> nTotal;
  numbers.resize(nTotal, 0);
  for (size_t i = 0; i < nTotal; i++) {
    std::cin >> numbers[i];
  }
}

int main()
{
  std::vector<int> Alice;
  std::vector<int> Bob;
  std::vector<int> Carlson;

  inputNumbers(Alice);
  inputNumbers(Bob);
  inputNumbers(Carlson);

  std::vector<int> temporary;
  temporary.reserve(256);  // Some evristics
  std::set_intersection(Alice.begin(), Alice.end(),
                        Bob.begin(), Bob.end(),
                        std::back_inserter(temporary));

  std::vector<int> team;
  team.reserve(256);  // Some evristics
  std::set_intersection(temporary.begin(), temporary.end(),
                        Carlson.begin(), Carlson.end(),
                        std::back_inserter(team));

  std::cout << team.size() << std::endl;
  return 0;
}
