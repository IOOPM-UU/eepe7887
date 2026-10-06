#include "hash_table.h"
#include "common.h"
#include "hash_table_iterator.h"
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
	ht->buckets = calloc(No_Buckets, sizeof(entry_t));  	
	ht->hash_fn = hash_fn;
  	ht->key_eq_fn = key_eq_fn;
	ht->load_factor = 0.75;
	ht->bucket_count = No_Buckets;
  	return ht;
}
/*
ioopm_hash_table_t *ioopm_modular_hash_table_create(ioopm_hash_function *hash_fn, ioopm_eq_function *key_eq_fn, size_t size, float load_factor)
{
	

	ioopm_hash_table_t *ht = calloc(1, sizeof(ioopm_hash_table_t));
	ht->hash_fn = hash_fn;
  	ht->key_eq_fn = key_eq_fn;
	ht->load_factor = load_factor;
	ht->size = size;
	return ht;
}
*/

bool size_check(ioopm_hash_table_t *ht)
{
	return ht->size >= ht->bucket_count * ht->load_factor;
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
 	for (size_t i = 0; i < ht->bucket_count; i++)
  	{
    	entry_t *current = ht->buckets[i].next;
     	while (current != NULL)
    	{
      		current = entry_destroy(current);
     	}
   	}
	free(ht->buckets);
   	free(ht);
}

static void rehash(ioopm_hash_table_t *ht)
{

	size_t primes[] = {17, 31, 67, 127, 257, 509, 1021, 2053, 4099, 8191, 16381};
	size_t array_size = sizeof(primes) / sizeof(primes[0]); 
	size_t i = 0;
	while (i < array_size && primes[i] <= ht->bucket_count)
	{
    	i++;
	}
	if (i == array_size)
	{
    	return; 
	}

	size_t new_count = primes[i];
	size_t old_buckets = ht->bucket_count;
	entry_t *old_entries = ht->buckets;

	ht->buckets = calloc(new_count, sizeof(entry_t));
	ht->bucket_count = new_count;
	
	for(size_t i = 0; i < old_buckets; i++)
	{
		entry_t *current = old_entries[i].next;
		while(current != NULL)
		{
			entry_t *next = current->next;
      		size_t modul = ht->hash_fn(current->key) % new_count;
      		current->next = ht->buckets[modul].next; 
      		ht->buckets[modul].next = current;
      		current = next;
		}

    }
	free(old_entries);
}

static entry_t *find_previous_entry(ioopm_hash_table_t *ht, elem_t *key)
{
	size_t bucket = ht->hash_fn(*key) % ht->bucket_count;

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
	if(size_check(ht))
	{
		rehash(ht);
	}
  	entry_t *previous = find_previous_entry(ht, key);

   	if (previous->next != NULL)
    {
    	previous->next->value = value;
    }
    else
    {
      	previous->next= entry_create(key, value, NULL);
		ht->size++;
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
		ht->size--;
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
  	for(size_t i = 0; i < ht->bucket_count; i++)
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

   	for(size_t i = 0; i < ht->bucket_count; i++)
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




