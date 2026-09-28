#include "hash_table.h"
#include "hash_table_iterator.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct entry entry_t;

struct entry {
    char *key;
    int value;
    entry_t *next;
};

struct hash_table {
    //DODGE: hard-docing number of buckets as 17
    //NOTE: addressing this dodge is optional
    entry_t buckets[17];                                    //Kan använda en variabel istället för 17 för att slippa hardcodad storlek
};

struct hash_table_iterator
{
  ioopm_hash_table_t *ht;
  int current_bucket;
  entry_t *current_entry;
};

static size_t string_knr_hash(const char *str) {
    size_t result = 0;

    while (*str != '\0') {
        result = result * 31 + ((unsigned char) *str);
        str++;
    }
    return result;
}

ioopm_hash_table_t *ioopm_hash_table_create(void) {
    //Allocate zeroed-out space for a ioopm_hash_table_t = 17 pointers to entry_t's
    return calloc(1, sizeof(ioopm_hash_table_t));
}

static entry_t *entry_create(char *key, int value, entry_t *next) {
    entry_t *entry = malloc(sizeof(entry_t));                       //Skulle kunna använda calloc för att vara säker på att slippa unpredictable behaviour.

    entry->key = key;
    entry->value = value;
    entry->next = next;

    return entry;
}

static entry_t *entry_destroy(entry_t *entry) {
    free(entry);
    return NULL;
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) {
    //loop through buckets
    for (int i = 0; i < 17; i++) {

        entry_t *current = &ht->buckets[i];
        current = current->next;
        entry_t *next;

        while (current != NULL) {
            next = current->next;
            entry_destroy(current);
            current = next;
        }
    }
    free(ht);
}

static entry_t *find_previous_entry(ioopm_hash_table_t *ht, char *key) {
    size_t bucket = string_knr_hash(key) % 17;

    entry_t *previous = &ht->buckets[bucket];
    entry_t *current = previous->next;

    while (current != NULL && strcmp(current->key, key) != 0) {
        if (current->next != NULL) {  //Onödig if/else sats i denna funktion. På grund av if-satsen i lookup och insert.
            previous = current;
            current = current->next;
        } else {
            return current;
        }
    }
    return previous;
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, char *key, int value) {
    //find previous entry, or the last entry if the key does not exist
    entry_t *previous = find_previous_entry(ht, key);

    //if the key exists, update the value, otherwise create a new entry
    if (previous->next != NULL) {
        previous->next->value = value;
    } else {
        previous->next = entry_create(key, value, NULL);
    }
}

bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, char *key, int *result) {
    //find previous entry, or the last entry if the key does not exist
    entry_t *previous = find_previous_entry(ht, key);

    //if the key exists, return the value, otherwise, indicate that the lookup failed
    if (previous->next != NULL) {
        *result = previous->next->value;
        return true;
    } else {
        return false;
    }
}

bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, char *key, int *result) {

    entry_t *previous = find_previous_entry(ht, key);
    entry_t *current = previous->next;                  //Kan använda någon tidigare funktion för att se om noden existerar, städa upp koden!

    //check if find_previous returned the last entry
    if (previous->next != NULL) {           
        //if not the last entry, check if there is an entry after the current
        if (current->next != NULL) {
            //redirect pointer from entry before current to point at entry after current
            previous->next = current->next;
            entry_destroy(current);
            return true;
        } else {
            //if there is no entry after current, make the pointer from previous point to NULL
            previous->next = NULL;
        }
        //change result to removed value, destroy entry and return true
        *result = current->value;
        entry_destroy(current);
        return true;
    } else {
        return false;
    }
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, char *key) {
    int val;
    return ioopm_hash_table_lookup(ht, key, &val);
}

static int bucket_size(entry_t *bucket) {
    int i = 0;
    while (bucket != NULL) {
        i++;
        bucket = bucket->next;
    }
    return i;
}

int ioopm_hash_table_size(ioopm_hash_table_t *ht) {
    int no_buckets = 17;
    int size = 0;
    for (int i = 0; i < no_buckets; i++) {
        size += bucket_size(ht->buckets[i].next);
    }
    return size;
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht) {            //Blir väldigt hög tidskomplexitet med denna lösning. (varje buckets första entry finns i början av bucketen)
    if (ioopm_hash_table_size(ht) != 0) {
        return false;
    } else {
        return true;
    }
}

static void advance_iterator_state(ioopm_hash_table_iterator_t *it) {
    // advance to the next entry in the bucket
  it->current_entry = it->current_entry->next;

  // if it was null advance to the next bucket
  if (it->current_entry == NULL)
  {
    it->current_bucket += 1;

    // if the next bucket existed, update the current entry
    if (it->current_bucket != 17)
    {
      it->current_entry = &it->ht->buckets[it->current_bucket];
     }
  }
}

static void skip_sentinel_nodes(ioopm_hash_table_iterator_t *it) {
    while (it->current_bucket != 17 && it->current_entry == &it->ht->buckets[it->current_bucket]) {
        advance_iterator_state(it);
    }
}

ioopm_hash_table_iterator_t *ioopm_hash_table_iterator_create(ioopm_hash_table_t *ht) {
    ioopm_hash_table_iterator_t *it = malloc(sizeof(ioopm_hash_table_iterator_t));
    it->ht = ht;
    it->current_bucket = 0;                     
    it->current_entry = &ht->buckets[0];
    skip_sentinel_nodes(it);
    return it;
}

void ioopm_hash_table_iterator_destroy(ioopm_hash_table_iterator_t *it) {
    free(it);
}

bool ioopm_hash_table_iterator_at_end(ioopm_hash_table_iterator_t *it) {
    return it->current_bucket == 17;
}

void ioopm_hash_table_iterator_advance(ioopm_hash_table_iterator_t *it) {
    advance_iterator_state(it);
    skip_sentinel_nodes(it);
}

char *ioopm_hash_table_iterator_current_key(ioopm_hash_table_iterator_t *it) {
    return it->current_entry->key;
}

int ioopm_hash_table_iterator_current_value(ioopm_hash_table_iterator_t *it) {
    return it->current_entry->value;
}