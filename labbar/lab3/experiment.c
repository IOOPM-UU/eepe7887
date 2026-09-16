#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"


extern char *strdup(const char *);

typedef union { 
  int   int_value;
  float float_value;
  char *string_value;
} answer_t;

typedef bool check_func(char*);
typedef answer_t convert_func(char*);

bool not_empty(char *str)
{
    return strlen(str) > 0;
}

bool is_number(char *str)
{
    if ((str[0] == 45 && strlen(str) > 1) || isdigit(str[0]))
    {
    for (int i = 1; i < strlen(str); i++){
        if (isdigit(str[i])){
            continue;
        }
        else {
            return false;
        }
    }
    }
    else {
        return false;
    }
    return true;
}


answer_t ask_question(char *question, check_func *check, convert_func *convert) {
    int buf_siz = 255;
    char buf[buf_siz];
    printf("%s", question);
    while(read_string(buf, buf_siz) == 0 || !check(buf)){
        printf("%s", question);
        }
    

    answer_t answer = convert(buf);
    return answer;
}

int ask_question_int(char *question)
{
  answer_t answer = ask_question(question, is_number, (convert_func *) atoi);
  return answer.int_value; // svaret som ett heltal
}

char *ask_question_string(char *question)
{
  return ask_question(question, not_empty, (convert_func *) strdup).string_value;
}

int main(void){

    ask_question_int("Säg een siffra: ");
    ask_question_string("Säg ett ord: ");
    return 0;
}