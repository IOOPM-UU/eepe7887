/// cat.c
#include <stdio.h>

void cat(char *filename)
{
  FILE *f = fopen(filename, "r");
  int c = fgetc(f);
    int rowcount = 1;
    printf("%d  ", rowcount);
    
  while (c != EOF)
  {
    fputc(c, stdout);
    if(c == '\n'){
        rowcount++;
        printf("%d  ", rowcount);
    }
   
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