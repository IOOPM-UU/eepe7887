#include <stdio.h>

 void print(char *str)
{
  char *end = str;
  while (*end != '\0'){ 
    putchar(*end);
    ++end;

}
  

}
int main(int argc, char *argv[]){
   
    
for (int i = 1; i < argc; ++i)
    {
    print(argv[i]);
    puts("\n");
    }
    return 0;
}