#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int string_length(char *str)
{
    int n = 0;

    while (str[n] != '\0')
    {
        n++;
    }

    return n;
}


int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Usage: %s words or string", argv[0]);
  }
  else
  {
    for (int i = 1; i < argc; ++i)
    {
      int expected = strlen(argv[i]);
      int actual   = string_length(argv[i]);
      printf("strlen(\"%s\")=%d\t\tstring_length(\"%s\")=%d\n",
             argv[i], expected, argv[i], actual);
    }
  }
  return 0;
}