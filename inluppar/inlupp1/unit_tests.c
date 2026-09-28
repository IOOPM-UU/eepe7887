#include "hash_table.h"
#include "hash_table_iterator.h"
#include <CUnit/Basic.h>
#include "utils.h"
#define No_Buckets 17



void test_create_destroy()
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create();
   CU_ASSERT_PTR_NOT_NULL(ht);
   ioopm_hash_table_destroy(ht);
}

void test_insert_once()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key = "abc";
  int value = 123;

  // check that key is not in ht
  int result = 0;
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, 0);

  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, value);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_insert_inuse()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key = "abc";
  int value = 123;
  int value2 = 456;

  // check that key is not in ht
  int result = 0;
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, 0);

  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, value);

  result = 0;
  ioopm_hash_table_insert(ht, key, value2);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, value2);
  
  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_remove_entry()
{
  int result = 3;
  char *key = "abc";
  int value = 123;
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_insert(ht, key, value);
  ioopm_hash_table_remove(ht, key);
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
  ioopm_hash_table_destroy(ht);

}

void test_remove_noexist_entry()
{
  int result = 3;
  char *key = "abc";
  char *key_noexist = "bcc";
  int value = 123;
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_FALSE(ioopm_hash_table_remove(ht, key_noexist));
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  ioopm_hash_table_destroy(ht);

}

void test_is_number(void) {
  CU_ASSERT_TRUE(is_number("42"));
  CU_ASSERT_TRUE(is_number("-10"));
}

void test_has_key_empty()
{
  // Create a hash table and check if it has some key k (it shouldn't).
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *k = "abc";

  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, k));
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);

  ioopm_hash_table_destroy(ht);
}

void test_has_key_single()
{
  // Create a hash table and insert some key k. Check if it has the key k
  // (it should). Also check if it has some other key k2 (it shouldn't).
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *k = "abc";
  char *k2 = "xyz";
  int value = 123;

  ioopm_hash_table_insert(ht, k, value);

  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, k));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, k2));
  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 1);

  ioopm_hash_table_destroy(ht);
}

void test_has_key_multiple()
{
  // Create a hash table and insert keys k1, k2 and k3. Check if all three
  // keys are present (they should be). Also check if it has some other
  // key k4 (it shouldn't).
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *k1 = "abc";
  char *k2 = "def";
  char *k3 = "ghi";
  char *k4 = "jkl";

  ioopm_hash_table_insert(ht, k1, 1);
  ioopm_hash_table_insert(ht, k2, 2);
  ioopm_hash_table_insert(ht, k3, 3);

  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, k1));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, k2));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, k3));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, k4));
  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 3);

  ioopm_hash_table_destroy(ht);
}

void test_has_key_insert_remove()
{
  // Create a hash table and insert key k, and immediately remove it.
  // Check if it has key k (it shouldn't).
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *k = "abc";
  int value = 123;

  ioopm_hash_table_insert(ht, k, value);
  ioopm_hash_table_remove(ht, k);

  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, k));
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);

  ioopm_hash_table_destroy(ht);
}

void test_has_key_remove_one_of_many()
{
  // Create a hash table and insert keys k1, k2 and k3. Remove key k2.
  // Check if it has keys k1 and k3 (it should). Check if it has key k2
  // (it shouldn't).
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *k1 = "abc";
  char *k2 = "def";
  char *k3 = "ghi";

  ioopm_hash_table_insert(ht, k1, 1);
  ioopm_hash_table_insert(ht, k2, 2);
  ioopm_hash_table_insert(ht, k3, 3);

  ioopm_hash_table_remove(ht, k2);

  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, k1));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, k3));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, k2));
  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 2);

  ioopm_hash_table_destroy(ht);
}

void test_iterate_over_empty_hash()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  bool at_end = ioopm_hash_table_iterator_at_end(it);
  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);

  CU_ASSERT_TRUE(at_end);
}

void test_iterate_hash_once()
{
  char *k = "abc";
  int value = 123;
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_insert(ht, k, value);
  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  int current_value = ioopm_hash_table_iterator_current_value(it);
  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);
  CU_ASSERT_EQUAL(current_value, 123);
}


void test_iterator_several_entries()
{
  char *keys[3] = {"abc", "qwe", "asd"};
  int values[3] = {0, 1, 2};

  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  for (int i = 0; i != 3; ++i)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }

  int iteration_count = 0;

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(it))
  {
    iteration_count++;
    ioopm_hash_table_iterator_advance(it);
  }

  ioopm_hash_table_destroy(ht);
  ioopm_hash_table_iterator_destroy(it);
  CU_ASSERT_EQUAL(iteration_count, 3);
}


void test_iterator_entries_visited_once()
{
  char *keys[3] = {"abc", "qwe", "asd"};
  int values[3] = {0, 1, 2};

  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  for (int i = 0; i != 3; ++i)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }

  int iteration_count = 0;

  int count_1 = 0;
  int count_2 = 0;
  int count_3 = 0;

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(it))
  {
    char *current_key = ioopm_hash_table_iterator_current_key(it);

    if(strcmp(current_key, "abc") == 0)
    {
      count_1++;
    }
    else if(strcmp(current_key, "qwe") == 0)
    {
      count_2++;
    }
    else if(strcmp(current_key, "asd") == 0)
    {
      count_3++;
    }
    iteration_count++;
    ioopm_hash_table_iterator_advance(it);
  }

  ioopm_hash_table_destroy(ht);
  ioopm_hash_table_iterator_destroy(it);

  CU_ASSERT_EQUAL(count_1, 1);
  CU_ASSERT_EQUAL(count_2, 1);
  CU_ASSERT_EQUAL(count_3, 1);  
}


void test_entries_in_same_bucket()
{
  char *keys[3] = {"a", "r", "ac"};
  int values[3] = {0, 1, 2};
  int count_1 = 0;
  int count_2 = 0;
  int count_3 = 0;

  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  
  int iteration_count = 0;
  for (int i = 0; i != 3; ++i)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
   while (!ioopm_hash_table_iterator_at_end(it))
  {
    char *current_key = ioopm_hash_table_iterator_current_key(it);

    if(strcmp(current_key, "a") == 0)
    {
      count_1++;
    }
    else if(strcmp(current_key, "r") == 0)
    {
      count_2++;
    }
    else if(strcmp(current_key, "ac") == 0)
    {
      count_3++;
    }
    iteration_count++;
    ioopm_hash_table_iterator_advance(it);
  }
 
  ioopm_hash_table_destroy(ht);
  ioopm_hash_table_iterator_destroy(it);
  CU_ASSERT_EQUAL(count_1, 1);
  CU_ASSERT_EQUAL(count_2, 1);
  CU_ASSERT_EQUAL(count_3, 1); 
  CU_ASSERT_EQUAL(iteration_count, 3);

}

int main() {
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("My awesome test suite", NULL, NULL);
  if (my_test_suite == NULL ) {
      // If the test suite could not be added, tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
  }

  // This is where we add the test functions to our test suite.
  // For each call to CU_add_test we specify the test suite, the
  // name or description of the test, and the function that runs
  // the test in question. If you want to add another test, just
  // copy a line below and change the information
  if (
    ((CU_add_test(my_test_suite, "Basic tests of is_number", test_is_number) == NULL) || 
    (CU_add_test(my_test_suite, "Test create/destroy", test_create_destroy) == NULL) ||
    (CU_add_test(my_test_suite, "Test insert once", test_insert_once) == NULL) ||
    (CU_add_test(my_test_suite, "Test insert and remove once", test_remove_entry) == NULL) ||
    (CU_add_test(my_test_suite, "Test has_key on empty table", test_has_key_empty) == NULL) ||
    (CU_add_test(my_test_suite, "Test has_key with single key", test_has_key_single) == NULL) ||
    (CU_add_test(my_test_suite, "Test has_key with multiple keys", test_has_key_multiple) == NULL) ||
    (CU_add_test(my_test_suite, "Test has_key after insert and remove", test_has_key_insert_remove) == NULL) ||
    (CU_add_test(my_test_suite, "Test has_key after removing one of many keys", test_has_key_remove_one_of_many) == NULL) ||
    (CU_add_test(my_test_suite, "Test iterate emptry hash", test_iterate_over_empty_hash) == NULL) ||
    (CU_add_test(my_test_suite, "Test iterate hash once", test_iterate_hash_once) == NULL) ||
    (CU_add_test(my_test_suite, "Test iterate severel", test_iterator_several_entries) == NULL) ||
    (CU_add_test(my_test_suite, "Test visit ince", test_iterator_entries_visited_once) == NULL) ||
    (CU_add_test(my_test_suite, "Test entries in same bucket", test_entries_in_same_bucket) == NULL) ||
    (CU_add_test(my_test_suite, "Test remove no exist", test_remove_noexist_entry) == NULL) ||
    (CU_add_test(my_test_suite, "Test insert inuse", test_insert_inuse) == NULL)

  )
  )
    {
      // If adding any of the tests fails, we tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
    }

  // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
  // Use CU_BRM_NORMAL to only print errors and a summary
  CU_basic_set_mode(CU_BRM_VERBOSE);

  // This is where the tests are actually run!
  CU_basic_run_tests();

  // Tear down CUnit before exiting
  CU_cleanup_registry();
  return CU_get_error();
}