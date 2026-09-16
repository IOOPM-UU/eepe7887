#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>




int print(char *str) {
    int n = 0;
   
   while (str[n] != '\0')
    {
        char letr = str[n];
        putchar(letr);
        ++n;
    }
    return 0;
}

int println(char *str) {
    int n = 0;
   while (str[n] != '\0')
    {
        char letr = str[n];
        putchar(letr);
        ++n;
    }
    putchar('\n');

    return 0;
}


int main(int argc, char *argv[]){
   
    
for (int i = 1; i < argc; ++i)
    {
    print(argv[i]);

    }
    return 0;
}
