#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int gissa_tal(int siffra, int slumpsiffra) {
    for(int i = 0; i <= 15; i++){
        if (siffra < slumpsiffra) {
            ask_question_int("För litet!");
        }
        else if (siffra > slumpsiffra) {
            ask_question_int("För stort!");
        }
        else{
            
            break;
        }
        
    }
return 0;
}

int main(void){
    char *namn;
    int användar_tal;
    int random_tal = random() % 1000;
    namn = ask_question_string("skriv in ditt namn:");
    printf("Du %s, jag tänker på ett tal ... kan du gissa vilket?", namn);
    gissa_tal(användar_tal, random_tal);
    return 0;
    

}