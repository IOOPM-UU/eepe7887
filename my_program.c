#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("Usage: %s [number]\n", argv[0]);
    return 1;
  }
  int upper_limit = atoi(argv[1]);

  int sum;
  int idx = 0;
  while (idx < 10) {
    sum += idx;
    idx++;
  }
  printf("The sum of the first %d integers is: %d\n", upper_limit, sum);
  return 0;
}