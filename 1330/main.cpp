#include <iostream>
#include <stdint.h>
#include <vector>
#include <cmath>
#include <stdio.h>

inline size_t getPow2(size_t nValue)
{
  size_t nLevel = 0;
  while ((2u << nLevel) <= nValue)
    ++nLevel;
  return nLevel;
}

inline size_t getLeftAligned(size_t value, size_t aligment)
{
  size_t r = value % aligment;
  return (r) ? value - r : value;
}

inline size_t getRightAligned(size_t value, size_t aligment)
{
  size_t r = value % aligment;
  return (r) ? value + (aligment - r) : value;
}

struct IndexedData
{
  IndexedData(std::vector<int32_t>&& values)
  {
    m_Data.push_back(std::move(values));
    buildIndex();
  }

  void buildIndex()
  {
    size_t nTotalLevels = getPow2(m_Data[0].size()) + 1;
    m_Data.resize(nTotalLevels);
    for (size_t nLevel = 1; nLevel < nTotalLevels; ++nLevel) {
      std::vector<int32_t>& levelBlocks     = m_Data[nLevel];
      std::vector<int32_t>& downLevelBlocks = m_Data[nLevel - 1];
      levelBlocks.reserve(downLevelBlocks.size() / 2);
      for (size_t i = 1; i < downLevelBlocks.size(); i += 2) {
        levelBlocks.push_back(downLevelBlocks[i] + downLevelBlocks[i - 1]);
      }
    }
  }

  int32_t getSumm(size_t begin, size_t end)
  {
    if (begin == end)
      return m_Data[0][begin];

    size_t nLevel          = getPow2(end - begin + 1);
    size_t nLevelBlockSize = 1u << nLevel;

    size_t nAlignedBegin = getRightAligned(begin, nLevelBlockSize);
    size_t nAlignedEnd   = getLeftAligned(end + 1, nLevelBlockSize);

    size_t nFirstBlock = nAlignedBegin / nLevelBlockSize;
    size_t nLastBlock  = nAlignedEnd / nLevelBlockSize;

    int32_t value = 0;
    std::vector<int32_t> const& nLevelBlocks = m_Data[nLevel];
    for (size_t i = nFirstBlock; i < nLastBlock; i++) {
      value += nLevelBlocks[i];
    }
    if (begin < nAlignedBegin)
      value += getSumm(begin, nAlignedBegin - 1);
    if (end >= nAlignedEnd)
      value += getSumm(nAlignedEnd, end);
    return value;
  }

  std::vector<std::vector<int32_t>> m_Data;
};

inline int rand(int from, int to)
{
  return from + (double(std::rand()) / RAND_MAX) * (to - from);
}

int main()
{
  uint16_t N = 0;
  std::cin >> N;
  std::vector<int> values;
  values.resize(N);
  for (size_t i = 0; i < N; ++i)
    std::cin >> values[i];

  IndexedData data(std::move(values));

  uint32_t Q = 0;
  int i = 0;
  int j = 0;
  std::cin >> Q;
  for(size_t q = 0; q < Q; ++q) {
    scanf("%d%d", &i, &j);
    printf("%d\n", data.getSumm(i - 1, j - 1));
  }
  return 0;
}

// Alternative solution:
//int main()
//{
//  uint16_t N = 0;
//  std::cin >> N;
//  int *values = new int[N + 1];
//  values[0] = 0;
//  for (size_t i = 1; i <= N; ++i) {
//    std::cin >> values[i];
//    values[i] += values[i - 1];
//  }

//  uint32_t Q = 0;
//  int i = 0;
//  int j = 0;
//  std::cin >> Q;
//  for(size_t q = 0; q < Q; ++q) {
//    scanf("%d%d", &i, &j);
//    printf("%d\n", values[j] - values[i - 1]);
//  }
//  return 0;
//}
