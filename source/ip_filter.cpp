#include <stdint.h>
#include <functional>
#include <tuple>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#ifdef AUTOTESTS_MODE
#include <gtest/gtest.h>
#endif

using IP     = std::vector<uint8_t>;
using IPPool = std::vector<IP>;

std::ostream& operator<<(std::ostream& out, IP const& ip)
{
  for (size_t i = 0; i < ip.size(); ++i)
    out << (i ? "." : "") << static_cast<int>(ip[i]);
  return out;
}

std::ostream& operator<<(std::ostream& out, IPPool const& pool)
{
  for (size_t i = 0; i < pool.size(); ++i)
    out << (i ? "\n" : "") << pool[i];
  return out;
}

// Returns substring from @nBeginFrom to first @separator occure, and position of
// @separator (or npos)
// ("",  '.', 0)             -> ["",    std::string::npos]
// ("192.168.0.10", '.', 0)  -> ["192", 3]
// ("192.168.0.10", '.', 4)  -> ["168", 7]
// ("192.168.0.10", '.', 8)  -> ["0",   9]
// ("192.168.0.10", '.', 10) -> ["10",  std::string::npos]
std::tuple<std::string, std::string::size_type>
readNextToken(std::string const& sLine, char separator, size_t nBeginFrom)
{
  auto nSeparatorPosition = sLine.find_first_of(separator, nBeginFrom);
  return std::make_tuple(sLine.substr(nBeginFrom, nSeparatorPosition - nBeginFrom),
                         nSeparatorPosition);
}

inline std::string readFirstToken(std::string const& sLine, char separator)
{
  std::string sResult;
  std::string::size_type nSeparatorPosition = 0;
  std::tie(sResult, nSeparatorPosition) = readNextToken(sLine, separator, 0);
  return sResult;
}

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(std::string const& str, char splitter)
{
  std::vector<std::string> r;
  std::string::size_type nBeginFrom = 0;
  while (nBeginFrom != std::string::npos) {
    std::string sNextPart;
    std::tie(sNextPart, nBeginFrom) = readNextToken(str, splitter, nBeginFrom);
    r.push_back(std::move(sNextPart));
    if (nBeginFrom != std::string::npos)
      ++nBeginFrom;
  }
  return r;
}

IP parseIP(std::vector<std::string> const& sOctets)
{
  if (sOctets.size() != 4)
    return IP();
  IP ip;
  for (std::string const& sOctet : sOctets) {
    int nOctetValue = atoi(sOctet.c_str());
    if (nOctetValue > 0xFF || nOctetValue < 0)
      return IP();
    ip.push_back(static_cast<uint8_t>(nOctetValue));
  }
  return ip;
}

IPPool readIpPool()
{
  IPPool pool;
  for(std::string line; std::getline(std::cin, line);)
  {
    std::string sIP = readFirstToken(line, '\t');
    IP ip = parseIP(split(sIP, '.'));
    if (!ip.empty())
      pool.push_back(std::move(ip));
  }
  return pool;
}

void printPoolSelectively(std::ostream& out, IPPool const& pool,
                          std::function<bool(IP const& ip)> predicate)
{
  for (IP const& ip : pool)
    if (predicate(ip))
      out << ip << "\n";
}

int main(int argc, char *argv[])
{
#ifdef AUTOTESTS_MODE
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
#else
  try
  {
    IPPool ipPool = readIpPool();

    // reverse lexicographically sort
    std::sort(ipPool.begin(), ipPool.end(),
              [](IP const& lhs, IP const& rhs) {
                assert(lhs.size() == 4);
                assert(rhs.size() == 4);
                for (size_t i = 0; i < 4; ++i) {
                  if (lhs[i] != rhs[i])
                    return lhs[i] > rhs[i];
                }
                return false;
              });

    std::cout << ipPool << std::endl;

    // First byte should be equal to 1
    printPoolSelectively(std::cout, ipPool, [](IP const& ip) { return ip[0] == 1; });

    // First byte should be equal to 46 and second byte should be equal to 70
    printPoolSelectively(std::cout, ipPool,
                         [](IP const& ip) { return ip[0] == 46 && ip[1] == 70; });

    // Any byte is equal to 46
    printPoolSelectively(
          std::cout, ipPool,
          [](IP const& ip) {
            for (size_t i = 0; i < ip.size(); i++)
              if (ip[i] == 46)
                return true;
            return false;
          });
  }
  catch(const std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
#endif
}

#ifdef AUTOTESTS_MODE
TEST(readTillSeparator_tests, success_case)
{
  // ("",  '.', 0)             -> ["",    std::string::npos]
  // ("192.168.0.10", '.', 0)  -> ["192", 3]
  // ("192.168.0.10", '.', 4)  -> ["168", 7]
  // ("192.168.0.10", '.', 8)  -> ["0",   9]
  // ("192.168.0.10", '.', 10) -> ["10",  std::string::npos]

  std::string const sLine = "192.168.10";

  std::string sResult;
  std::string::size_type nSeparatorPosition = 0;

  // ("192.168.10", '.', 0)  -> ["192", 3]
  std::tie(sResult, nSeparatorPosition) = readNextToken(sLine, '.', 0);
  ASSERT_EQ("192", sResult);
  ASSERT_EQ(3, nSeparatorPosition);

  // ("192.168.10", '.', 4)  -> ["168", 7]
  std::tie(sResult, nSeparatorPosition) = readNextToken(sLine, '.', 4);
  ASSERT_EQ("168", sResult);
  ASSERT_EQ(7, nSeparatorPosition);

  // ("192.168.10", '.', 8)  -> ["10", std::string::npos]
  std::tie(sResult, nSeparatorPosition) = readNextToken(sLine, '.', 8);
  ASSERT_EQ("10", sResult);
  ASSERT_EQ(std::string::npos, nSeparatorPosition);
}

TEST(readTillSeparator_tests, empty_string)
{
  std::string sResult;
  std::string::size_type nSeparatorPosition = 0;
  std::tie(sResult, nSeparatorPosition) = readNextToken("", '.', 0);
  ASSERT_TRUE(sResult.empty());
  ASSERT_EQ(std::string::npos, nSeparatorPosition);
}

TEST(readTillSeparator_tests, string_ends_with_separator)
{
  std::string const sLine = "192.";
  std::string sResult;
  std::string::size_type nSeparatorPosition = 0;

  // ("192.", '.', 0)  -> ["192", 3]
  std::tie(sResult, nSeparatorPosition) = readNextToken(sLine, '.', 0);
  ASSERT_EQ("192", sResult);
  ASSERT_EQ(3, nSeparatorPosition);
  // ("192.", '.', 4)  -> ["", std::string::npos]
  std::tie(sResult, nSeparatorPosition) = readNextToken(sLine, '.', 4);
  ASSERT_TRUE(sResult.empty());
  ASSERT_EQ(std::string::npos, nSeparatorPosition);
}

TEST(split_tests, success_case)
{
  std::string const sLine = "192.168.0.100";
  std::vector<std::string> strings = split(sLine, '.');
  ASSERT_EQ(4, strings.size());
  EXPECT_EQ("192", strings[0]);
  EXPECT_EQ("168", strings[1]);
  EXPECT_EQ("0",   strings[2]);
  EXPECT_EQ("100", strings[3]);
}
#endif
