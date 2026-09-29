#include "hash_table.h"
#include "hash_table_iterator.h"
#include <CUnit/Basic.h>
#include "utils.h"
#include "linked_list.h"


void test_create_empty_list()
{
    ioopm_list_t *list = ioopm_list_create();
    CU_ASSERT_TRUE(ioopm_list_is_empty(list));
    ioopm_list_destroy(list);
}
void test_append_list_once()
{
    int value = 12;
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_append(list, value);
    int head =ioopm_list_head(list);
    int tail = ioopm_list_last(list);
    ioopm_list_destroy(list);
    CU_ASSERT_EQUAL(head, value);
    CU_ASSERT_EQUAL(tail, value);
}

void test_several_appends()
{

    int value1 = 12;
    int value2 = 13;
    int value3 = 11;

    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, value1);
    ioopm_list_append(list, value2);
    ioopm_list_append(list, value3);

    int head =ioopm_list_get(list, 0);
    int middle = ioopm_list_get(list, 1);
    int tail = ioopm_list_get(list, 2);
    

    ioopm_list_destroy(list);   

    CU_ASSERT_EQUAL(head, value1);
    CU_ASSERT_EQUAL(middle, value2);
    CU_ASSERT_EQUAL(tail, value3);

}

void test_several_prepends()
{
      int value1 = 12;
    int value2 = 13;
    int value3 = 11;

    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_prepend(list, value1);
    ioopm_list_prepend(list, value2);
    ioopm_list_prepend(list, value3);

    int head =ioopm_list_head(list);
    int middle = ioopm_list_get(list, 1);
    int tail = ioopm_list_last(list);
    
    ioopm_list_destroy(list);   

    CU_ASSERT_EQUAL(tail, value1);
    CU_ASSERT_EQUAL(middle, value2);
    CU_ASSERT_EQUAL(head, value3);
}

void test_append_prepend_insert()
{
    int value1 = 12; // appendas sist
    int value2 = 13; // prependas först
    int value3 = 7;  // insertas i mitten

    size_t one = 1;
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, value1);   // list: [12]
    ioopm_list_prepend(list, value2);  // list: [13, 12]
    ioopm_list_insert(list, one, value3); // list: [13, 7, 12]

    int first = ioopm_list_get(list, 0);
    int middle = ioopm_list_get(list, 1);
    int last = ioopm_list_get(list, 2);

    int head = ioopm_list_head(list);
    int tail = ioopm_list_last(list);

    ioopm_list_destroy(list);

    CU_ASSERT_EQUAL(first, value2);
    CU_ASSERT_EQUAL(middle, value3);
    CU_ASSERT_EQUAL(last, value1);

    CU_ASSERT_EQUAL(head, value2);
    CU_ASSERT_EQUAL(tail, value1);
}


void test_remove_from_list()
{
    int value1 = 12;
    int value2 = 13;
    int value3 = 11;

    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, value1);
    ioopm_list_append(list, value2);
    ioopm_list_append(list, value3);
    // list: [12, 13, 11]

    int removed = ioopm_list_remove(list, 1); // ta bort mittenelementet
    // list: [12, 11]

    int head = ioopm_list_head(list);
    int tail = ioopm_list_last(list);
    int size = ioopm_list_size(list);

    ioopm_list_destroy(list);

    CU_ASSERT_EQUAL(removed, value2);
    CU_ASSERT_EQUAL(head, value1);
    CU_ASSERT_EQUAL(tail, value3);
    CU_ASSERT_EQUAL(size, 2);
}

void test_remove_first_and_last()
{
    int value1 = 1;
    int value2 = 2;
    int value3 = 3;

    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, value1);
    ioopm_list_append(list, value2);
    ioopm_list_append(list, value3);
    // list: [1, 2, 3]

    int removed_first = ioopm_list_remove(list, 0);
    // list: [2, 3]
    int removed_last = ioopm_list_remove(list, ioopm_list_size(list) - 1);
    // list: [2]

    int only_element = ioopm_list_head(list);
    int size = ioopm_list_size(list);

    ioopm_list_destroy(list);

    CU_ASSERT_EQUAL(removed_first, value1);
    CU_ASSERT_EQUAL(removed_last, value3);
    CU_ASSERT_EQUAL(only_element, value2);
    CU_ASSERT_EQUAL(size, 1);
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
    ((CU_add_test(my_test_suite, "Test empty list", test_create_empty_list) == NULL ||
    CU_add_test(my_test_suite, "TEST APPEND and head/tail", test_append_list_once) == NULL ||
    CU_add_test(my_test_suite, "TEST several appends", test_several_appends) == NULL ||
    CU_add_test(my_test_suite, "TEST several prepends", test_several_prepends) == NULL ||
    CU_add_test(my_test_suite, "TEST append, prepend and insert", test_append_prepend_insert) == NULL ||
    CU_add_test(my_test_suite, "TEST remove from middle", test_remove_from_list) == NULL ||
    CU_add_test(my_test_suite, "TEST remove first and last", test_remove_first_and_last) == NULL)
    
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