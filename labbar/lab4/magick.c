#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char *magick(char **arr1, char **arr2, char **arr3, int arrlen)
{
    char buf[255];
    char *word1 = arr1[random() % (arrlen - 1)];
    char *word2 = arr2[random() % (arrlen - 1)];
    char *word3 = arr3[random() % (arrlen - 1)];
    

    for(int i = 0; i <= strlen(word1); i++) {
        buf[i] = word1[i];
        i++;
    }
    
    for(int i = 0; i <= strlen(word2); i++) {
        buf[i + strlen(word1) + 2] = word2[i];
        i++;
    }
        
    for(int i = 0; i <= strlen(word3); i++) {
        buf[i + strlen(word1) + strlen(word2) + 3] = word3[i];
        i++;
    }

return strdup(buf);

}

int main(){
char *array1[] = { "Laser",        "Polka",    "Extra" };
char *array2[] = { "förnicklad",   "smakande", "ordinär" };
char *array3[] = { "skruvdragare", "kola",     "uppgift" };

char *str = magick(array1, array2, array3, 3); // 3 = längden på arrayerna

puts(str); // Polka-ordinär skruvdragare
    return 0;
}