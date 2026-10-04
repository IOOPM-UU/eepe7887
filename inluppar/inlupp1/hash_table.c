#include "hash_table.h"
#include "common.h"
//#include "hash_table_iterator.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define No_Buckets 17
#define int_elem(x)   ((elem_t) { .i = (x) })
#define bool_elem(x)  ((elem_t) { .b = (x) })
#define ptr_elem(x)   ((elem_t) { .p = (x) })
#define string_elem(x) ((elem_t) { .s = (x) })


typedef struct entry entry_t;

struct entry
{
  	elem_t key;     // holds the key
  	elem_t value;     // holds the value
  	entry_t *next; // points to the next entry (possibly NULL)
};


struct hash_table_iterator
{
  	ioopm_hash_table_t *ht;
  	size_t current_bucket;
  	entry_t *current_entry;
};


struct hash_table
{
  	// NOTE: addressing this dodge is optional.
  	entry_t buckets[No_Buckets];
  	ioopm_hash_function *hash_fn;
  	ioopm_eq_function *key_eq_fn;
};



static entry_t *entry_create(elem_t *key, elem_t value, entry_t *next)
{
  	entry_t *entry = calloc(1, sizeof(entry_t));
  	entry->key = *key;
  	entry->value = value;
  	entry->next = next;
  	return entry;
}

/// @brief Creates a hashtable
/// @param hash_fn hashing function used to hash all of the keys
/// @param key_eq_fn equality function to check equality between keys
/// @return hashtable
ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function *hash_fn, ioopm_eq_function *key_eq_fn)
{
  	ioopm_hash_table_t *ht = calloc(1, sizeof(ioopm_hash_table_t));
  	ht->hash_fn = hash_fn;
  	ht->key_eq_fn = key_eq_fn;
  	return ht;
}

static entry_t *entry_destroy(entry_t *entry)
{
  	entry_t *next = entry->next;
  	free(entry);
  	entry = next;
  	return entry; // Returns the next element while freeing the entry we want to destroy
}

/// @brief destroys the hashtable
/// @param ht the hashtable to be destroyed
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
 	for (size_t i = 0; i < No_Buckets; i++)
  	{
    	entry_t *current = ht->buckets[i].next;
     	while (current != NULL)
    	{
      		current = entry_destroy(current);
     	}
   	}
   	free(ht);
}

static entry_t *find_previous_entry(ioopm_hash_table_t *ht, elem_t *key)
{
	size_t bucket = ht->hash_fn(*key) % No_Buckets;

	entry_t *previous = &ht->buckets[bucket];
	entry_t *current = ht->buckets[bucket].next;
	while (current != NULL && !ht->key_eq_fn(current->key, *key))
	{
   		previous = current;
     	current = current->next;
    }
    return previous;
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t *key, elem_t value)
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

bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t *key, elem_t *result)
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

bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t *key)
{
  	elem_t result;
   	entry_t *previous = find_previous_entry(ht, key);

    if (ioopm_hash_table_lookup(ht, key, &result))
    {
    	previous->next = entry_destroy(previous->next);

     	return true;
    }
    else
    {
    	return false;
    }
}


bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t *key)
{
  	elem_t result;
   	return ioopm_hash_table_lookup(ht, key, &result);
}


bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
  	for(size_t i = 0; i < No_Buckets; i++)
   	{
    	entry_t *bucket = ht->buckets[i].next;
     	if(bucket != NULL)
    	{
      		return false;
     	}
    }
   	return true;
}


size_t ioopm_hash_table_size(ioopm_hash_table_t *ht)
{
  	size_t size = 0;

   	for(size_t i = 0; i < No_Buckets; i++)
    {
    	entry_t *bucket = ht->buckets[i].next;
     	while(bucket != NULL)
      	{
      		entry_t *next = bucket->next;
       		bucket = next;
         	size++;
       	}
    }
    return size;
}



/**
* @author Alex Egeberg, Eemeli Peura
* @date Sep 2026
* @brief Simple hash table iterator
*
* Hash table iterators provide an interface to iterate through all entries in a hash table.
* An iterator is either positioned at an entry, called the current entry, or it is positioned at-the-end, if it has already iterated through all entries.
* If the underlying hash table of an iterator is modified using any non-iterator function, the iterator is invalidated and should not be used anymore.
*
*/

typedef struct hash_table_iterator ioopm_hash_table_iterator_t;

static void advance_iterator_state(ioopm_hash_table_iterator_t *it)
{
  	// advance to the next entry in the bucket
   	it->current_entry = it->current_entry->next;

    // if it was null advance to the next bucket
    if (it->current_entry == NULL)
    {
    	it->current_bucket += 1;

     	// if the next bucket existed, update the current entry
      	if (it->current_bucket != No_Buckets)
    	{
      		it->current_entry = &it->ht->buckets[it->current_bucket];
     	}
    }
}

static void skip_sentinel_nodes(ioopm_hash_table_iterator_t *it)
{
  	while (it->current_bucket != No_Buckets &&
          it->current_entry == &it->ht->buckets[it->current_bucket])
   	{
    	advance_iterator_state(it);
    }
}

/// @brief Create an iterator for a hash table.
/// @param ht hash table to iterate over
/// @return a new iterator positioned at the first entry if it exists, and positioned at-the-end if ht is empty
ioopm_hash_table_iterator_t *ioopm_hash_table_iterator_create(ioopm_hash_table_t *ht)
{
    ioopm_hash_table_iterator_t *it = malloc(sizeof(ioopm_hash_table_iterator_t));
    it->ht = ht;
    it->current_bucket = 0;
    it->current_entry = &ht->buckets[0];
    skip_sentinel_nodes(it);
    return it;
}

/// @brief Destroy an iterator and free its memory
/// @param it iterator to destroy
void ioopm_hash_table_iterator_destroy(ioopm_hash_table_iterator_t *it)
{
  	free(it);
}

/// @brief Check if the current element exists, or equivalently, if it is positioned at an entry
/// @param it iterator operated upon
/// @return true iff the current element exists
bool ioopm_hash_table_iterator_at_end(ioopm_hash_table_iterator_t *it)
{
  	return it->current_bucket == No_Buckets;
}

/// @brief Move the iterator forward to the next entry if it exists or to at-the-end if no more entries exist
/// @pre it is positioned at an entry
/// @param it iterator operated upon
void ioopm_hash_table_iterator_advance(ioopm_hash_table_iterator_t *it)
{
  	advance_iterator_state(it);
   	skip_sentinel_nodes(it);
}

/// @brief Get the key of the current entry
/// @pre it is positioned at an entry
/// @param it iterator operated upon
/// @return the key of the current entry
elem_t *ioopm_hash_table_iterator_current_key(ioopm_hash_table_iterator_t *it)
{
  	return &it->current_entry->key;
}

/// @brief Get the value of the current entry
/// @pre it is positioned at an entry
/// @param it iterator operated upon
/// @return the value if the current entry
elem_t ioopm_hash_table_iterator_current_value(ioopm_hash_table_iterator_t *it)
{
  	return it->current_entry->value;
}
