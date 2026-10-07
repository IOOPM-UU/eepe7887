#pragma once
#include <stdbool.h>
#include <stddef.h> 
#include "common.h"

/**
* @file hash_table.h
* @author Alex Egeberg Eemeli Peura
* @date write the date you started working on this
* @brief Simple hash table that maps string keys to integer values.
*
* Here typically goes a more extensive explanation of what the header
* defines. Doxygens tags are words preceeded by either a backslash @\
* or by an at symbol @@. 
*
*/

typedef struct hash_table ioopm_hash_table_t;

typedef struct entry entry_t;

struct entry
{
  	elem_t key;     // holds the key
  	elem_t value;     // holds the value
  	entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  	// NOTE: addressing this dodge is optional.
  	entry_t **buckets;
	float load_factor;
	size_t size;
    size_t bucket_count;
  	ioopm_hash_function *hash_fn;
  	ioopm_eq_function *key_eq_fn;
};


/// @brief Create a new hash table
/// @param hash_fn hashing function used for hashing
/// @param key_eq_fn equality function 
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function *hash_fn, ioopm_eq_function *key_eq_fn);


/// @brief 
/// @param hash_fn 
/// @param key_eq_fn 
/// @param capacity 
/// @param load_factor 
/// @return 
ioopm_hash_table_t *ioopm_modular_hash_table_create(ioopm_hash_function *hash_fn, ioopm_eq_function *key_eq_fn, size_t capacity, float load_factor);

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, const elem_t *key, elem_t value);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @param result a pointer to an element that will be changed to a pointer to key if it is found
/// @return the value mapped to by key if true else return false
bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, const elem_t *key, elem_t *result);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @return the next value after the removed if true else false
bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, const elem_t *key);

/// @brief checks if the key is in the hashtable
/// @param ht the hashtable operated upon
/// @param key the key to find
/// @return true if found else false
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, const elem_t *key);

/// @brief checks if the hashtable is empty
/// @param ht the hashtable operated upon
/// @return true if empty else false
bool ioopm_hash_table_is_empty(const ioopm_hash_table_t *ht);

/// @brief returns the hashtables size
/// @param ht the hashtable operated upon
/// @return the size of the hashtable
size_t ioopm_hash_table_size(const ioopm_hash_table_t *ht);
