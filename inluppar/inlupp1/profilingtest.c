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



static size_t int_hash(elem_t key)
{
  return (size_t) key.i;
}

static bool int_eq(elem_t a, elem_t b)
{
  return a.i == b.i;
}


void test_many_entries_slow()
{
  const int N = 100000;
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash, int_eq);

  // Sätt in många nycklar (kedjorna blir långa med 17 buckets)
  for (int i = 0; i < N; i++)
  {
    elem_t key = int_elem(i);
    ioopm_hash_table_insert(ht, &key, int_elem(i * 10));
  }
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), N);

  // Slå upp alla nycklar
  int all_found = 0;
  for (int i = 0; i < N; i++)
  {
    elem_t key = int_elem(i);
    elem_t result = int_elem(-1);
    if (ioopm_hash_table_lookup(ht, &key, &result) && result.i == i * 10)
    {
      all_found++;
    }
  }
  CU_ASSERT_EQUAL(all_found, N);

  // Nycklar som saknas (hela kedjan genomsöks)
  int missing = 0;
  for (int i = N; i < N + N / 2; i++)
  {
    elem_t key = int_elem(i);
    if (!ioopm_hash_table_has_key(ht, &key))
    {
      missing++;
    }
  }
  CU_ASSERT_EQUAL(missing, N / 2);

  // Ta bort varannan nyckel
  int removed = 0;
  for (int i = 0; i < N; i += 2)
  {
    elem_t key = int_elem(i);
    if (ioopm_hash_table_remove(ht, &key))
    {
      removed++;
    }
  }
  CU_ASSERT_EQUAL(removed, N / 2);
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), N / 2);

  ioopm_hash_table_destroy(ht);
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
    (CU_add_test(my_test_suite, "Basic tests of is_number", test_many_entries_slow) == NULL)
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
