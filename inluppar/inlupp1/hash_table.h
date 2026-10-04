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


/// @brief Create a new hash table
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function *hash_fn, ioopm_eq_function *key_eq_fn);

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t *key, elem_t value);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @return the value mapped to by key if true else return false
bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t *key, elem_t *result);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @return the next value after the removed if true else false
bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t *key);

/// @brief checks if the key is in the hashtable
/// @param ht the hashtable operated upon
/// @param key the key to find
/// @return true if found else false
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t *key);

/// @brief checks if the hashtable is empty
/// @param ht the hashtable operated upon
/// @return true if empty else false
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);

/// @brief returns the hashtables size
/// @param ht the hashtable operated upon
/// @return the size of the hashtable
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht);
