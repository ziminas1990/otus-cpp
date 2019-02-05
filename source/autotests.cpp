#include "Allocator.h"

#include <cstdint>
#include <gtest/gtest.h>
#include <set>

#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(Allocator, GetOnlyUniquePointers)
{
  std::set<std::uint64_t*> pointers;
  awesome_allocator<uint64_t, 16> allocator;
  for (size_t i = 0; i < 16 * 100; ++i)
  {
    std::uint64_t *ptr = allocator.allocate(1);
    ASSERT_TRUE(pointers.insert(ptr).second) << "on iteration #" << i;
  }
}
