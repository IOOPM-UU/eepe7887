#include "hash_table.h"
#include "common.h"
#include "hash_table_iterator.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define int_elem(x)   ((elem_t) { .i = (x) })
#define bool_elem(x)  ((elem_t) { .b = (x) })
#define ptr_elem(x)   ((elem_t) { .p = (x) })
#define string_elem(x) ((elem_t) { .s = (x) })


static entry_t *entry_create(const elem_t *key, elem_t value, entry_t *next)
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
  	return ioopm_modular_hash_table_create(hash_fn, key_eq_fn, 17, 0.75);
}

ioopm_hash_table_t *ioopm_modular_hash_table_create(ioopm_hash_function *hash_fn, ioopm_eq_function *key_eq_fn, size_t capacity, float load_factor)
{
	ioopm_hash_table_t *ht = calloc(1, sizeof(ioopm_hash_table_t));

	ht->buckets = calloc(capacity, sizeof(entry_t *));
	ht->hash_fn = hash_fn;
	ht->key_eq_fn = key_eq_fn;
	ht->load_factor = load_factor;
	ht->bucket_count = capacity;

	return ht;
}

bool growth_check(ioopm_hash_table_t *ht)
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
    	entry_t *current = ht->buckets[i];
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
	entry_t **old_entries = ht->buckets;

	ht->buckets = calloc(new_count, sizeof(entry_t));
	ht->bucket_count = new_count;
	
	for(size_t i = 0; i < old_buckets; i++)
	{
		entry_t *current = old_entries[i];
		while(current != NULL)
		{
			entry_t *next = current->next;
      		size_t modul = ht->hash_fn(current->key) % new_count;
      		current->next = ht->buckets[modul]; 
      		ht->buckets[modul] = current;
      		current = next;
		}

    }
	free(old_entries);
}

static entry_t **find_link(ioopm_hash_table_t *ht, const elem_t *key)
{
	size_t bucket = ht->hash_fn(*key) % ht->bucket_count;

	entry_t **current = &(ht->buckets[bucket]); // ht->buckets[bucket] är bucketens första länk (platsen som innehåller en pekare till första entryn), '&' ger adressen till den
	while (*current != NULL && !ht->key_eq_fn((*current)->key, *key)) // så länge länken pekar på en entry och entryns nyckel inte är den vi letar efter
	{
     	current = &((*current)->next); // ska vara av typ **, därav '&' framför det hela
    }
    return current;
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, const elem_t *key, elem_t value)
{
  	entry_t **link = find_link(ht, key);

   	if (*(link) != NULL)
    {
    	(*link)->value = value;
    }
    else
    {
		ht->size++;
      	*link = entry_create(key, value, NULL);

		if(growth_check(ht))
		{
			rehash(ht);
		}
    }
}

bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, const elem_t *key, elem_t *result)
{
	entry_t **link = find_link(ht, key);
  	// if the key exists, return the value, otherwise, indicate that the lookup failed
	if ((*link) != NULL)
  	{
    	*result = (*link)->value;
    	return true;
  	}
  	else
  	{
    	return false;
  	}
}

bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, const elem_t *key)
{
   	entry_t **link = find_link(ht, key);

    if (*link != NULL)
    {
    	*link = entry_destroy(*link);
		ht->size--;
     	return true;
    }
    else
    {
    	return false;
    }
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, const elem_t *key)
{
  	elem_t result;
   	return ioopm_hash_table_lookup(ht, key, &result);
}


bool ioopm_hash_table_is_empty(const ioopm_hash_table_t *ht)
{
  	for(size_t i = 0; i < ht->bucket_count; i++)
   	{
    	entry_t *bucket = ht->buckets[i];
     	if(bucket != NULL)
    	{
      		return false;
     	}
    }
   	return true;
}

size_t ioopm_hash_table_size(const ioopm_hash_table_t *ht)
{
    return ht->size;
}
