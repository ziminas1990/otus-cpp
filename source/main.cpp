#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <string>
#include "print_ip.h"

int main(int, char*[])
{
  // Hmmm... gcc 4.8.4 (travis-ci) was confused about this line
  //using namespace std::string_literals;

  std::cout << print_ip(char(-1)) << std::endl;
  std::cout << print_ip(short(0)) << std::endl;
  std::cout << print_ip(int(2130706433)) << std::endl;
  std::cout << print_ip(long(8875824491850138409)) << std::endl;
  std::cout << print_ip("127.0.0.1") << std::endl;
  std::cout << print_ip(std::vector<int>{1,2,3,4,5}) << std::endl;
  std::cout << print_ip(std::list<int>{2048,1024,512,256,128}) << std::endl;
  return 0;
}
