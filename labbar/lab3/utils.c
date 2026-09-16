#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include <ctype.h>


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

extern char *strdup(const char *);


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


answer_t ask_question(char *question, check_func *check, convert_func *convert) 
{
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

