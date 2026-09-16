#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

struct item {
    char *Name;
    char *Desc;
    int Price;
    char *Shelf;

};

typedef struct item item_t;

void print_item(item_t *item)
{   
    int örerest = item->Price % 100;
    int pris = (item->Price - örerest)/ 100; 
    printf("Item: %s \nDesc: %s \nPrice: %d.%d SEK\n Shelf: %s \n"item->Name, item->Desc, örerest, pris, item->Shelf);
}

item_t make_item(char *namn, char *Desc, int pris, char *Hylla){
    item_t i = {.Name = namn, .Desc = Desc, .Price = pris, .Shelf = Hylla};
    return i;
}
/*
item_t input_item() 
{
    char *name = ask_question_string("Varans namn!");
    char *Desc = ask_question_string("Beskriv varan!");
    int price = ask_question_int("Varans pris i ören!")
    
}
*/

char *str magick(char *arr1, char *arr2, char *arr3, int arrlen)
{
    char *buf[255];
  
    char *word1 = arr1[random() % (arrlen - 1)];
    char *word2 = arr2[random() % (arrlen - 1)];
    char *word3 = arr3[random() % (arrlen - 1)];
    buf[0] = word1;
    buf[1] = " ";
    buf[2] = word2;
    buf[3] = " ";
    buf[4] = word2;
    buf[5] = "\0";
    



}

int main(){
    char *array1[] = { "Laser",        "Polka",    "Extra" };
char *array2[] = { "förnicklad",   "smakande", "ordinär" };
char *array3[] = { "skruvdragare", "kola",     "uppgift" };

char *str = magick(array1, array2, array3, 3); // 3 = längden på arrayerna

puts(str); // Polka-ordinär skruvdragare
    return 0;
}