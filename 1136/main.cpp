#include <iostream>
#include <stdint.h>

uint16_t* inputData(size_t& nTotal)
{
  std::cin >> nTotal;
  uint16_t* nId = new uint16_t[nTotal];
  for(size_t i = 0; i < nTotal; ++i)
    std::cin >> nId[i];
  return nId;
}

struct Node
{
  Node(uint16_t nId) : nId(nId) {}
  ~Node() { /*Hey, common, it's just a contest problem!*/ }

  Node*    pLeft  = nullptr;
  Node*    pRight = nullptr;
  uint16_t nId    = 0;
};

Node* buildSubtree(uint16_t* nIds, size_t nTotalIds)
{
  // In general, nIds array contains:
  // [L1, L2... LN, R1, R2 ... RN, C]  or  [{L}, {R}, C]
  // where:
  // 1. each element from {R} > C
  // 2. each element from {L} < C
  // "C" will be a root of tree, {R} and {L} will be used to recursevly build right and
  // left subtrees
  // But first we should find size of {R} and {L}
  Node* pRoot = new Node(nIds[nTotalIds - 1]);

  size_t nTotalL = 0;
  while (nTotalL < nTotalIds - 1 && nIds[nTotalL] < pRoot->nId)
    ++nTotalL;
  size_t nTotalR = nTotalIds - nTotalL - 1;

  pRoot->pLeft  = nTotalL ? buildSubtree(nIds,           nTotalL) : nullptr;
  pRoot->pRight = nTotalR ? buildSubtree(nIds + nTotalL, nTotalR) : nullptr;
  return pRoot;
}

void printTree(Node* pRoot)
{
  if (!pRoot)
    return;
  printTree(pRoot->pRight);
  printTree(pRoot->pLeft);
  std::cout << pRoot->nId << "\n";
}

int main()
{
  size_t nTotal = 0;
  uint16_t* nId = inputData(nTotal);
  if (!nTotal)
    return 0;
  Node* pNode = buildSubtree(nId, nTotal);
  printTree(pNode);
  std::cout << std::endl;
  return 0;
}
