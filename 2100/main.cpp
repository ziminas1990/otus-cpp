#include <iostream>
#include <stdint.h>
int main()
{
  size_t nInvitedGuests = 0;
  std::cin >> nInvitedGuests;
  size_t nTotalGuests = nInvitedGuests + 2;
  for(size_t i = 0; i < nInvitedGuests; i++) {
    std::string guest;
    std::cin >> guest;
    if (guest.find('+') != std::string::npos)
      nTotalGuests++;
  }
  if (nTotalGuests == 13)
    ++nTotalGuests;
  std::cout << nTotalGuests * 100 << std::endl;
  return 0;
}
