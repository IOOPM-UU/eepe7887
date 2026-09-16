#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef int int_fold_func(int, int);


int foldl_int_int(int numbers[], int numbers_siz, int_fold_func *f)
{
  int result = 0;

  for (int i = 0; i < numbers_siz; ++i)
  {
    result = f(result, numbers[i]);
  }

  return result;
}

int add(int a, int b)
{
  return a + b;
}

int sum(int numbers[], int numbers_siz) {
    
    return foldl_int_int(numbers, numbers_siz, add);

}

int main(int argc, char *argv[]){
    int len = argc;
    int numbers[len - 1];
    for (int i = 1; i < len; i++) {
          numbers[i - 1] = atoi(argv[i]);        
    }
    printf("%d \a", sum(numbers, len));
    puts("");


    return 0;
}
