#include <iostream>
#include <stdint.h>

struct Position
{
  Position(int x, int y) : x(x), y(y) {}

  bool isValid() const {
    return x > 0 && x < 9 && y > 0 && y < 9;
  }

  Position getOffsetPosition(int offsetX, int offsetY) const
  {
    return Position(x + offsetX, y + offsetY);
  }

  int x;
  int y;
};

Position inputPosition()
{
  char column = 0;
  int  row    = 0;
  std::cin >> column >> row;
  return Position(column - 'a' + 1, row);
}

int main()
{
  int offsetsX[] = { -2, -1, 1, 2,  2,  1, -1, -2 };
  int offsetsY[] = {  1,  2, 2, 1, -1, -2, -2, -1 };

  size_t nTotalTests = 0;
  std::cin >> nTotalTests;
  for (size_t i = 0; i < nTotalTests; i++) {
    Position position = inputPosition();
    int nTotal = 0;
    for (size_t i = 0; i < 8; i++) {
      Position newPosition = position.getOffsetPosition(offsetsX[i], offsetsY[i]);
      if (newPosition.isValid())
        nTotal++;
    }
    std::cout << nTotal << std::endl;
  }
  return 0;
}
