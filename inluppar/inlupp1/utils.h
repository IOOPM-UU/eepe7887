#ifndef __UTILS_H__
#define __UTILS_H__
#include <stdbool.h>

/// @brief union for an answer that can be either of the types inside the union
typedef union { 
  int   int_value;
  float float_value;
  char *string_value;
} answer_t;


typedef bool check_func(char*);

typedef answer_t convert_func(char*);


extern char *strdup(const char *);

/// @brief Reads a string and returns an int that represents the size of the string
/// @param buf the buffer
/// @param buf_siz the buffers size
/// @return 
int read_string(char *buf, int buf_siz);

/// @brief Takes in a string to check if it's a number or not
/// @param str a string
/// @return boolean true or false
bool is_number(char *str);

/// @brief Takes in a string to see if it's not empty
/// @param str a string
/// @return boolean true or false
bool not_empty(char *str);


#endif 