/// cat.c
#include <stdio.h>

void cp(char *filename)
{
  FILE *f = fopen(filename, "r");
  int c = fgetc(f);
    
  while (c != EOF)
  {
    fputc(c, stdout);
   
    c = fgetc(f);
  }
  puts("");
  fclose(f);
}



int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf(stdout, "Usage: %s fil1 ...\n", argv[0]);
  }
  else
  {
    for (int i = 1; i < argc; ++i)
    {
      cat(argv[i]);
    }
  }

  return 0;
}