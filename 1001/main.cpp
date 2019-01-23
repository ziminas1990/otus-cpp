#include <math.h>
#include <stdio.h>
#include <vector>

int main()
{
  std::vector<long long> inputData;
  inputData.reserve(1000);

  long long nValue = 0;
  while (scanf("%lld", &nValue) != EOF)
    inputData.push_back(nValue);

  for (auto it = inputData.rbegin(); it != inputData.rend(); ++it)
    printf("%.4f\n", std::sqrt(*it));
  return 0;
}
