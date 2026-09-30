#include "hash_table.h"
#include "hash_table_iterator.h"
#include <CUnit/Basic.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"
#define No_Buckets 17
#define int_elem(x)   ((elem_t) { .i = (x) })
#define bool_elem(x)  ((elem_t) { .b = (x) })
#define ptr_elem(x)   ((elem_t) { .p = (x) })
#define string_elem(x) ((elem_t) { .s = (x) })

// Hash and equality functions for string keys
static size_t string_hash(elem_t key)
{
  size_t result = 0;
  const char *str = key.s;
  while (*str != '\0')
  {
    result = result * 31 + ((unsigned char) *str);
    str++;
  }
  return result;
}

static bool string_eq(elem_t a, elem_t b)
{
  return strcmp(a.s, b.s) == 0;
}

static ioopm_hash_table_t *create_ht(void)
{
  return ioopm_hash_table_create(string_hash, string_eq);
}

void test_create_destroy()
{
  ioopm_hash_table_t *ht = create_ht();
  CU_ASSERT_PTR_NOT_NULL(ht);
  ioopm_hash_table_destroy(ht);
}

void test_insert_once()
{
  ioopm_hash_table_t *ht = create_ht();

  elem_t key = string_elem("abc");
  elem_t value = int_elem(123);

  // check that key is not in ht
  elem_t result = int_elem(0);
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, &key, &result));
  CU_ASSERT_EQUAL(result.i, 0);

  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, &key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, &key, &result));
  CU_ASSERT_EQUAL(result.i, value.i);

  ioopm_hash_table_destroy(ht);
}

void test_insert_inuse()
{
  ioopm_hash_table_t *ht = create_ht();

  elem_t key = string_elem("abc");
  elem_t value = int_elem(123);
  elem_t value2 = int_elem(456);

  elem_t result = int_elem(0);
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, &key, &result));
  CU_ASSERT_EQUAL(result.i, 0);

  ioopm_hash_table_insert(ht, &key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, &key, &result));
  CU_ASSERT_EQUAL(result.i, value.i);

  result.i = 0;
  ioopm_hash_table_insert(ht, &key, value2);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, &key, &result));
  CU_ASSERT_EQUAL(result.i, value2.i);

  ioopm_hash_table_destroy(ht);
}

void test_remove_entry()
{
  elem_t result = int_elem(3);
  elem_t key = string_elem("abc");
  elem_t value = int_elem(123);
  ioopm_hash_table_t *ht = create_ht();

  ioopm_hash_table_insert(ht, &key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_remove(ht, &key));
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, &key, &result));

  ioopm_hash_table_destroy(ht);
}

void test_remove_noexist_entry()
{
  elem_t result = int_elem(3);
  elem_t key = string_elem("abc");
  elem_t key_noexist = string_elem("bcc");
  elem_t value = int_elem(123);
  ioopm_hash_table_t *ht = create_ht();

  ioopm_hash_table_insert(ht, &key, value);
  CU_ASSERT_FALSE(ioopm_hash_table_remove(ht, &key_noexist));
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, &key, &result));

  ioopm_hash_table_destroy(ht);
}

void test_is_number(void)
{
  CU_ASSERT_TRUE(is_number("42"));
  CU_ASSERT_TRUE(is_number("-10"));
}

void test_has_key_empty()
{
  ioopm_hash_table_t *ht = create_ht();

  elem_t k = string_elem("abc");

  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, &k));
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);

  ioopm_hash_table_destroy(ht);
}

void test_has_key_single()
{
  ioopm_hash_table_t *ht = create_ht();

  elem_t k = string_elem("abc");
  elem_t k2 = string_elem("xyz");
  elem_t value = int_elem(123);

  ioopm_hash_table_insert(ht, &k, value);

  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, &k));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, &k2));
  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 1);

  ioopm_hash_table_destroy(ht);
}

void test_has_key_multiple()
{
  ioopm_hash_table_t *ht = create_ht();

  elem_t k1 = string_elem("abc");
  elem_t k2 = string_elem("def");
  elem_t k3 = string_elem("ghi");
  elem_t k4 = string_elem("jkl");

  ioopm_hash_table_insert(ht, &k1, int_elem(1));
  ioopm_hash_table_insert(ht, &k2, int_elem(2));
  ioopm_hash_table_insert(ht, &k3, int_elem(3));

  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, &k1));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, &k2));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, &k3));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, &k4));
  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 3);

  ioopm_hash_table_destroy(ht);
}

void test_has_key_insert_remove()
{
  ioopm_hash_table_t *ht = create_ht();

  elem_t k = string_elem("abc");
  elem_t value = int_elem(123);

  ioopm_hash_table_insert(ht, &k, value);
  ioopm_hash_table_remove(ht, &k);

  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, &k));
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);

  ioopm_hash_table_destroy(ht);
}

void test_has_key_remove_one_of_many()
{
  ioopm_hash_table_t *ht = create_ht();

  elem_t k1 = string_elem("abc");
  elem_t k2 = string_elem("def");
  elem_t k3 = string_elem("ghi");

  ioopm_hash_table_insert(ht, &k1, int_elem(1));
  ioopm_hash_table_insert(ht, &k2, int_elem(2));
  ioopm_hash_table_insert(ht, &k3, int_elem(3));

  ioopm_hash_table_remove(ht, &k2);

  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, &k1));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, &k3));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, &k2));
  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 2);

  ioopm_hash_table_destroy(ht);
}

void test_iterate_over_empty_hash()
{
  ioopm_hash_table_t *ht = create_ht();
  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  bool at_end = ioopm_hash_table_iterator_at_end(it);
  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);

  CU_ASSERT_TRUE(at_end);
}

void test_iterate_hash_once()
{
  elem_t k = string_elem("abc");
  elem_t value = int_elem(123);
  ioopm_hash_table_t *ht = create_ht();
  ioopm_hash_table_insert(ht, &k, value);

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  elem_t current_value = ioopm_hash_table_iterator_current_value(it);
  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);

  CU_ASSERT_EQUAL(current_value.i, 123);
}

void test_iterator_several_entries()
{
  elem_t keys[3] = {string_elem("abc"), string_elem("qwe"), string_elem("asd")};
  int values[3] = {0, 1, 2};

  ioopm_hash_table_t *ht = create_ht();
  for (int i = 0; i != 3; ++i)
  {
    ioopm_hash_table_insert(ht, &keys[i], int_elem(values[i]));
  }

  int iteration_count = 0;

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(it))
  {
    iteration_count++;
    ioopm_hash_table_iterator_advance(it);
  }

  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);
  CU_ASSERT_EQUAL(iteration_count, 3);
}

void test_iterator_entries_visited_once()
{
  elem_t keys[3] = {string_elem("abc"), string_elem("qwe"), string_elem("asd")};
  int values[3] = {0, 1, 2};

  ioopm_hash_table_t *ht = create_ht();
  for (int i = 0; i != 3; ++i)
  {
    ioopm_hash_table_insert(ht, &keys[i], int_elem(values[i]));
  }

  int count_1 = 0;
  int count_2 = 0;
  int count_3 = 0;

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(it))
  {
    elem_t *current_key = ioopm_hash_table_iterator_current_key(it);

    if (strcmp(current_key->s, "abc") == 0)
    {
      count_1++;
    }
    else if (strcmp(current_key->s, "qwe") == 0)
    {
      count_2++;
    }
    else if (strcmp(current_key->s, "asd") == 0)
    {
      count_3++;
    }
    ioopm_hash_table_iterator_advance(it);
  }

  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);

  CU_ASSERT_EQUAL(count_1, 1);
  CU_ASSERT_EQUAL(count_2, 1);
  CU_ASSERT_EQUAL(count_3, 1);
}

void test_entries_in_same_bucket()
{
  // "a", "r" and "ac" all hash to bucket 12 with a mod-17 string hash
  elem_t keys[3] = {string_elem("a"), string_elem("r"), string_elem("ac")};
  int values[3] = {0, 1, 2};
  int count_1 = 0;
  int count_2 = 0;
  int count_3 = 0;

  ioopm_hash_table_t *ht = create_ht();

  int iteration_count = 0;
  for (int i = 0; i != 3; ++i)
  {
    ioopm_hash_table_insert(ht, &keys[i], int_elem(values[i]));
  }

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(it))
  {
    elem_t *current_key = ioopm_hash_table_iterator_current_key(it);

    if (strcmp(current_key->s, "a") == 0)
    {
      count_1++;
    }
    else if (strcmp(current_key->s, "r") == 0)
    {
      count_2++;
    }
    else if (strcmp(current_key->s, "ac") == 0)
    {
      count_3++;
    }
    iteration_count++;
    ioopm_hash_table_iterator_advance(it);
  }

  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);

  CU_ASSERT_EQUAL(count_1, 1);
  CU_ASSERT_EQUAL(count_2, 1);
  CU_ASSERT_EQUAL(count_3, 1);
  CU_ASSERT_EQUAL(iteration_count, 3);
}

int main()
{
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  CU_pSuite my_test_suite = CU_add_suite("My awesome test suite", NULL, NULL);
  if (my_test_suite == NULL)
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
    (CU_add_test(my_test_suite, "Basic tests of is_number", test_is_number) == NULL) ||
    (CU_add_test(my_test_suite, "Test create/destroy", test_create_destroy) == NULL) ||
    (CU_add_test(my_test_suite, "Test insert once", test_insert_once) == NULL) ||
    (CU_add_test(my_test_suite, "Test insert and remove once", test_remove_entry) == NULL) ||
    (CU_add_test(my_test_suite, "Test has_key on empty table", test_has_key_empty) == NULL) ||
    (CU_add_test(my_test_suite, "Test has_key with single key", test_has_key_single) == NULL) ||
    (CU_add_test(my_test_suite, "Test has_key with multiple keys", test_has_key_multiple) == NULL) ||
    (CU_add_test(my_test_suite, "Test has_key after insert and remove", test_has_key_insert_remove) == NULL) ||
    (CU_add_test(my_test_suite, "Test has_key after removing one of many keys", test_has_key_remove_one_of_many) == NULL) ||
    (CU_add_test(my_test_suite, "Test iterate empty hash", test_iterate_over_empty_hash) == NULL) ||
    (CU_add_test(my_test_suite, "Test iterate hash once", test_iterate_hash_once) == NULL) ||
    (CU_add_test(my_test_suite, "Test iterate several", test_iterator_several_entries) == NULL) ||
    (CU_add_test(my_test_suite, "Test visit once", test_iterator_entries_visited_once) == NULL) ||
    (CU_add_test(my_test_suite, "Test entries in same bucket", test_entries_in_same_bucket) == NULL) ||
    (CU_add_test(my_test_suite, "Test remove no exist", test_remove_noexist_entry) == NULL) ||
    (CU_add_test(my_test_suite, "Test insert inuse", test_insert_inuse) == NULL)
  )
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();

  CU_cleanup_registry();
  return CU_get_error();
}