#include "hash_table.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define No_Buckets 17

typedef struct entry entry_t;

struct entry
{
  char *key;     // holds the key
  int value;     // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  // NOTE: addressing this dodge is optional.
  entry_t buckets[No_Buckets];
};

static size_t string_knr_hash(const char *str)
{
  size_t result = 0;
  while (*str != '\0')
  {
    result = result * 31 + ((unsigned char) *str);
    str++;
  }
  return result;
}

entry_t *entry_create(char *key, int value, entry_t *next)
{
  entry_t *entry = calloc(1, sizeof(entry_t));
  entry->key = key;
  entry->value = value;
  entry->next = next;
  return entry;
}

ioopm_hash_table_t *ioopm_hash_table_create(void) {
    return calloc(1, sizeof(ioopm_hash_table_t));
}

entry_t *destroy_entry(entry_t *entry)
 {
  entry_t *next = entry->next;
  free(entry);
  entry = next;
  return entry;
 }


void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) {
 for (size_t i = 0; i < No_Buckets; i++)
  {
    entry_t *current = ht->buckets[i].next;
    while (current != NULL)
    {
      current = destroy_entry(current);
    }
  }
   free(ht);
 return;
}

entry_t *find_previous_entry(ioopm_hash_table_t *ht, char *key)
{
  size_t bucket = string_knr_hash(key) % No_Buckets;
  
  entry_t *previous = &ht->buckets[bucket];
  entry_t *current = ht->buckets[bucket].next;
  while (current != NULL && strcmp(current->key, key) != 0)
  {
    previous = current;
    current = current->next;
  }
  return previous;
  }



void ioopm_hash_table_insert(ioopm_hash_table_t *ht, char *key, int value)
{

  entry_t *previous = find_previous_entry(ht, key);

  if (previous->next != NULL)
  {
    previous->next->value = value;
  }
  else
  {
      previous->next= entry_create(key, value, NULL);
  }
  
}



bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, char *key, int *result)
{
  entry_t *previous = find_previous_entry(ht, key);
  // if the key exists, return the value, otherwise, indicate that the lookup failed
  if (previous->next != NULL)
  {
    *result = previous->next->value;
    return true;
  }


  else
  {
    return false;
  }
}

bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, char *key)
{
  int result = 0;
  entry_t *previous = find_previous_entry(ht, key);
  

  if (ioopm_hash_table_lookup(ht, key, &result))
  {
    previous->next = destroy_entry(previous->next);
    
    return true;
  }
  else 
  {
    return false;
  }
}