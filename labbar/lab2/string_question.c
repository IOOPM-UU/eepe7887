#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int clear_input_buffer(void){
    int c;
 do
        {
          c = getchar();
        }
      while (c != '\n');
      putchar('\n');
      return 0;
    }

int read_string(char *buf, int buf_siz) {
    int count = -1;
    do{
        count++;
        buf[count] = getchar();
        
    }
    while (buf[count] !='\n' && count <= buf_siz - 1);

    buf[count] = '\0';
    return count;
}


int main(void)
{
    int buf_siz = 255;
    int read = 0;
    char buf[buf_siz];

    puts("Läs in en sträng:");
    read = read_string(buf, buf_siz);
    printf("'%s' (%d tecken)\n", buf, read);

    puts("Läs in en sträng till:");
    read = read_string(buf, buf_siz);
    printf("'%s' (%d tecken)\n", buf, read);

    return 0;
}