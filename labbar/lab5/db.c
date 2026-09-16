#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"

struct item 
{
    char *name;
    char *desc;
    int price;
    char *shelf;
};

typedef struct item item_t;

void print_item(item_t *i)
{   
    int ören = i->price % 100;
    int kronor = (i->price - ören) / 100;
    printf(" Name: %s\n Desc: %s\n Price: %d.%d\n Shelf: %s\n", i->name, i->desc, kronor, ören, i->shelf);
}

item_t make_item(char *name, char *desc, int price, char *shelf)
{
    item_t i = { .name = name, .desc = desc, .price = price, .shelf = shelf};
    return i;
}

item_t input_item()
{
    char *name = ask_question_string("Namn på vara: ");
    char *desc = ask_question_string("Skriv in en beskrvining: ");
    int pris = ask_question_int("Skriv pris i ören: ");
    char *shelf = ask_question_shelf("Skriv in vilken hylla ex (A25): ");
    item_t i = make_item(name, desc, pris, shelf);
    return i;
}

char *magick(char **a1, char **a2, char **a3, int len)
{
    char buf[255]; 
    char *word1 = a1[random() % (len - 1)];
    char *word2 = a2[random() % (len - 1)];
    char *word3 = a3[random() % (len - 1)];
    int count = 0;
    for (int i = 0; i < strlen(word1); i++)
        {
            buf[count] = word1[i];
            count++;
        }
        
        buf[count] = '-';
        count++;

    for (int i = 0; i < strlen(word2); i++)
        {
            buf[count] = word2[i];
            count++;
        }

        buf[count] = ' ';
        count++;

    for (int i = 0; i < strlen(word3); i++)
        {
            buf[count] = word3[i];
            count ++;
        }        

        buf[count] = '\0';
        count++;

    return strdup(buf);

}

void list_db(item_t *items, int no_items)
{
  int item_index = 0;
    for (int i = 0; i < no_items; ++i)
     {
      item_index = i + 1;
      printf("%d. %s\n", item_index, items[i].name);
     }
}

void edit_db(item_t *item, int no_items)
{
  int change_item = ask_question_int("Vilket item vill du ändra? Välj med nr av respektive item: ");
    if (change_item > 0 && change_item <= no_items)
    {
      puts("Item som ska ändras:");
      print_item(&item[change_item - 1]);
      item[change_item - 1] = input_item();
      list_db(item, no_items);
    }
    else 
    {
      printf("Måste vara index [1-%d] av items i databasen.", no_items);
    }
}

void add_item_to_db(item_t *item, int *no_items)
{
    puts("Lägg till ett item! ");
    item[*no_items] = input_item();
    ++*no_items;   
}

void remove_item(item_t *item, int *no_items)
{
  int remove_item = ask_question_int("Vilket item vill du ta bort? ");
    if (remove_item > 0 && remove_item <= *no_items)
    {
        for(int i = remove_item - 1; i < *no_items; i++){
            item[i] = item[i + 1];
            
        }
    --*no_items;
    }
    else 
    {
      printf("Måste vara index [1-%d] av items i databasen.", *no_items);
    }
}

void event_loop(item_t *db, int db_siz)
{
  
    char *menu_loop = "";

    while(strcmp(menu_loop, "A"))
    {
        menu_loop = ask_question_menu("Vad vill du göra? ");
        
        
        if(!strcmp(menu_loop, "L")) {
            add_item_to_db(db, &db_siz);
        }
        else if(!strcmp(menu_loop, "T")){
            remove_item(db, &db_siz);
        }
        else if(!strcmp(menu_loop, "R")){
            edit_db(db, db_siz);
        }
        else if(!strcmp(menu_loop, "H")){
            list_db(db, db_siz);
        }
        else{
            puts("Not implemented yet");
            continue;
        }


    }
}

int main(int argc, char *argv[])
{
  char *array1[] = {  "Laser",        "Polka",    "Extra"  }; // TODO: Lägg till!
  char *array2[] = { "förnicklad",   "smakande", "ordinär" }; // TODO: Lägg till!
  char *array3[] = { "skruvdragare", "kola",     "uppgift" }; // TODO: Lägg till!

  if (argc < 2)
  {
    printf("Usage: %s number\n", argv[0]);
  }
  else
  {
    item_t db[16]; // Array med plats för 16 varor
    int db_siz = 0; // Antalet varor i arrayen just nu

    int items = atoi(argv[1]); // Antalet varor som skall skapas

    if (items > 0 && items <= 16)
    {
      for (int i = 0; i < items; ++i)
      {
        // Läs in en vara, lägg till den i arrayen, öka storleksräknaren
        item_t item = input_item();
        db[db_siz] = item;
        ++db_siz;
      }
    }
    else
    {
      puts("Sorry, must have [1-16] items in database.");
      return 1; // Avslutar programmet!
    }

    for (int i = db_siz; i < 15; ++i)
      {
        char *name = magick(array1, array2, array3, 3); // TODO: Lägg till storlek
        char *desc = magick(array1, array2, array3, 3); // TODO: Lägg till storlek
        int price = random() % 200000;
        char shelf[] = { random() % ('Z'-'A') + 'A',
                         random() % 10 + '0',
                         random() % 10 + '0',
                         '\0' };
        item_t item = make_item(name, desc, price, strdup(shelf));

        db[db_siz] = item;
        ++db_siz;
      }

event_loop(db, db_siz);
  }
  return 0;
}