#include "hash_table.h"
#include "hash_table_iterator.h"
#include <CUnit/Basic.h>
#include "utils.h"
#include "linked_list.h"
#include "list_iterator.h"


void test_create_empty_it()
{
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);

    bool sentinel = ioopm_list_iterator_advance(iter);
    CU_ASSERT_TRUE(sentinel);

    CU_ASSERT_FALSE(ioopm_list_iterator_advance(iter));
    
    ioopm_list_iterator_destroy(iter);
    ioopm_list_destroy(list);
}

void test_iter_on_list()
{
    int value = 12;
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);
    ioopm_list_iterator_insert(iter, value);
    int current_value = ioopm_list_iterator_current(iter);
    CU_ASSERT_EQUAL(current_value, value);
    ioopm_list_iterator_destroy(iter);
    ioopm_list_destroy(list);
}

void test_iter_advance()
{
    int value_1 = 12;
    int value_2 = 26;
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);
    ioopm_list_iterator_insert(iter, value_1);
    ioopm_list_iterator_insert(iter, value_2);
    int first_value = ioopm_list_iterator_current(iter);
    ioopm_list_iterator_advance(iter);
    int second_value = ioopm_list_iterator_current(iter);
    CU_ASSERT_EQUAL(first_value, value_1);
    CU_ASSERT_EQUAL(second_value, value_2);
    ioopm_list_iterator_destroy(iter);
    ioopm_list_destroy(list);    



}

void test_iter_remove_and_insert()
{
    int value_1 = 12;
    int value_2 = 26;
    int value_3 = 2;
    int value_4 = 444;
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);
    ioopm_list_iterator_insert(iter, value_1);
    ioopm_list_iterator_insert(iter, value_2);
    int current_value = ioopm_list_iterator_current(iter);
    CU_ASSERT_EQUAL(current_value, value_1);
    ioopm_list_iterator_remove(iter);
    CU_ASSERT_EQUAL(ioopm_list_iterator_current(iter), value_2);
    ioopm_list_iterator_insert(iter, value_3);
    ioopm_list_iterator_insert(iter, value_4);
    ioopm_list_iterator_advance(iter);
    CU_ASSERT_EQUAL(ioopm_list_iterator_current(iter), value_4);
    ioopm_list_iterator_advance(iter);
    CU_ASSERT_EQUAL(ioopm_list_iterator_current(iter), value_3);
    ioopm_list_iterator_destroy(iter);
    ioopm_list_destroy(list);    

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
    ((CU_add_test(my_test_suite, "Test iter on empty list", test_create_empty_it) == NULL ||
    CU_add_test(my_test_suite, "Test iter on list", test_iter_on_list) == NULL ||
    CU_add_test(my_test_suite, "Test iter advance", test_iter_advance) == NULL ||
    CU_add_test(my_test_suite, "Test iter remove and insert", test_iter_remove_and_insert) == NULL)
    
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