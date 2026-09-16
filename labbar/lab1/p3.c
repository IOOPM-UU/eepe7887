#include <stdio.h>

int main(void)
{
 int x = 0; 
char *asterix = "*";
  for (int i = 1; i <=10; i++){
    for (int n = 1; n <= i; n++){
      x++;
      printf("%s", asterix);
    }
    printf("\n" );

  }
  printf("Totalt: %d\n", x);
  return 0;
}