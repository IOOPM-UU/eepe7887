#include "hash_table.h"
#include "hash_table_iterator.h"
#include "common.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define No_Buckets 17



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

// Detta är en hjälpfunktion för advance_iterator_state
static void skip_empty_buckets(ioopm_hash_table_iterator_t *it) {
	// if it was null advance to the next bucket
    while (it->current_entry == NULL && it->current_bucket != it->ht->bucket_count)
    {
    	it->current_bucket += 1;

     	// if the next bucket existed, update the current entry
<<<<<<< HEAD
      	if (it->current_bucket != No_Buckets)
=======
      	if (it->current_bucket != it->ht->bucket_count)
>>>>>>> 0841002914dbbedde3759eeb447c4b23fa7c1c98
    	{
      		it->current_entry = it->ht->buckets[it->current_bucket];
     	}
    }
<<<<<<< HEAD
}

static void advance_iterator_state(ioopm_hash_table_iterator_t *it)
{
  	// advance to the next entry in the bucket
   	it->current_entry = it->current_entry->next;

	// skip to the next non_empty bucket or the end if we're at the end of this bucket
	skip_empty_buckets(it);
}

=======
}

static void advance_iterator_state(ioopm_hash_table_iterator_t *it)
{
  	// advance to the next entry in the bucket
   	it->current_entry = it->current_entry->next;

	// skip to the next non_empty bucket or the end if we're at the end of this bucket
	skip_empty_buckets(it);
}
>>>>>>> 0841002914dbbedde3759eeb447c4b23fa7c1c98


/// @brief Create an iterator for a hash table.
/// @param ht hash table to iterate over
/// @return a new iterator positioned at the first entry if it exists, and positioned at-the-end if ht is empty
ioopm_hash_table_iterator_t *ioopm_hash_table_iterator_create(ioopm_hash_table_t *ht)
{
    ioopm_hash_table_iterator_t *it = calloc(1, sizeof(ioopm_hash_table_iterator_t));
    it->ht = ht;
    it->current_bucket = 0;
    it->current_entry = it->ht->buckets[0];
	skip_empty_buckets(it);
    return it;
}

void ioopm_hash_table_iterator_destroy(ioopm_hash_table_iterator_t *it)
{
  	free(it);
}

bool ioopm_hash_table_iterator_at_end(const ioopm_hash_table_iterator_t *it)
{
  	return it->current_bucket == No_Buckets;
}

/// @brief Move the iterator forward to the next entry if it exists or to at-the-end if no more entries exist
/// @pre it is positioned at an entry
/// @param it iterator operated upon
void ioopm_hash_table_iterator_advance(ioopm_hash_table_iterator_t *it)
{
  	advance_iterator_state(it);
}

elem_t *ioopm_hash_table_iterator_current_key(const ioopm_hash_table_iterator_t *it)
{
  	return &it->current_entry->key;
}

elem_t ioopm_hash_table_iterator_current_value(const ioopm_hash_table_iterator_t *it)
{
  	return it->current_entry->value;
}