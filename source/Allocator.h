#pragma once
#include <iostream>
#include <assert.h>
#include <cstdint>
#include <bitset>
#include <vector>

#define BLOCK_PREFIX "Block(" << this << ")::"

template <typename T, size_t nCapacity>
class awesome_allocator
{
public:
  using value_type = T;

  T* allocate(size_t nTotal)
  {
    assert(nTotal == 1);
    T* pChunk = nullptr;
    // searchinkg for free chunk in existance blocks
    for (Block& block : blocks) {
      pChunk = block.getChunk();
      if (pChunk)
        break;
    }
    // no free chunks - creating new block
    if (!pChunk) {
      std::cout << "... Creating new block" << std::endl;
      Block newBlock;
      newBlock.allocate();
      pChunk = newBlock.getChunk();
      blocks.push_back(std::move(newBlock));
    }
    return pChunk;
  }

  void deallocate(T* ptr, size_t nTotal)
  {
    assert(nTotal == 1);
    for (Block& block : blocks)
      if (block.freeChunk(ptr))
        return;
  }

private:

  class Block {
  public:
    Block() : pChunksCache(nullptr) {}
    Block(Block const& other) = delete;
    Block(Block&& other)
    {
      nUsedChunksMask = std::move(other.nUsedChunksMask);
      std::swap(pChunksCache, other.pChunksCache);
    }
    ~Block() {
      free(pChunksCache);
    }

    Block& operator=(Block && other) = default;

    void allocate() {
      pChunksCache = reinterpret_cast<T*>(malloc(nCapacity * sizeof(T)));
    }
    bool hasFreeChunk() const { return pChunksCache && !nUsedChunksMask.all(); }
    T* getChunk();
    bool freeChunk(T* pChunk);
    bool isContainChunk(T* pChunk) const;

  private:
    std::bitset<nCapacity> nUsedChunksMask;
    T* pChunksCache = nullptr;
  };

  std::vector<Block, std::allocator<awesome_allocator::Block>> blocks;
};

template<typename T, size_t nCapacity>
T* awesome_allocator<T, nCapacity>::Block::getChunk()
{
  if (!pChunksCache || !hasFreeChunk())
    return nullptr;
  size_t index = 0;
  while (nUsedChunksMask[index]) index++;
  nUsedChunksMask.set(index);
  return pChunksCache + index;
}

template<typename T, size_t nCapacity>
bool awesome_allocator<T, nCapacity>::Block::freeChunk(T* pChunk)
{
  if (!isContainChunk(pChunk))
    return false;
  size_t nIndex = pChunk - pChunksCache;
  nUsedChunksMask.reset(nIndex);
  return true;
}

template<typename T, size_t nCapacity>
bool awesome_allocator<T, nCapacity>::Block::isContainChunk(T* pChunk) const
{
  return pChunksCache && pChunk >= pChunksCache && (pChunk - pChunksCache < nCapacity);
}
