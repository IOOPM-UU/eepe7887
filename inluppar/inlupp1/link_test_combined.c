#include "hash_table.h"
#include "hash_table_iterator.h"
#include <CUnit/Basic.h>
#include "utils.h"
#include "linked_list.h"
#include "list_iterator.h"
#define int_elem(x)   ((elem_t) { .i = (x) })
#define bool_elem(x)  ((elem_t) { .b = (x) })
#define ptr_elem(x)   ((elem_t) { .p = (x) })
#define string_elem(x) ((elem_t) { .s = (x) })


void test_create_empty_it()
{
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);

    bool end_sentinel = ioopm_list_iterator_advance(iter);
    CU_ASSERT_TRUE(end_sentinel);
    CU_ASSERT_FALSE(ioopm_list_iterator_advance(iter));
    ioopm_list_iterator_destroy(iter);
    ioopm_list_destroy(list);
}

void test_iter_on_list()
{
    elem_t value = int_elem(12);
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);
    ioopm_list_iterator_insert(iter, value);
    elem_t current_value = ioopm_list_iterator_current(iter);
    CU_ASSERT_EQUAL(current_value.i, value.i);
    ioopm_list_iterator_destroy(iter);
    ioopm_list_destroy(list);
}

void test_iter_advance()
{
    elem_t value_1 = int_elem(12);
    elem_t value_2 = int_elem(26);
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);
    ioopm_list_iterator_insert(iter, value_1);
    ioopm_list_iterator_insert(iter, value_2);
    elem_t first_value = ioopm_list_iterator_current(iter);
    ioopm_list_iterator_advance(iter);
    elem_t second_value = ioopm_list_iterator_current(iter);
    CU_ASSERT_EQUAL(first_value.i, value_1.i);
    CU_ASSERT_EQUAL(second_value.i, value_2.i);
    ioopm_list_iterator_destroy(iter);
    ioopm_list_destroy(list);    



}

void test_iter_remove_and_insert()
{
    elem_t value_1 = int_elem(12);
    elem_t value_2 = int_elem(26);
    elem_t value_3 = int_elem(2);
    elem_t value_4 = int_elem(444);
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);
    ioopm_list_iterator_insert(iter, value_1);
    ioopm_list_iterator_insert(iter, value_2);
    elem_t current_value = ioopm_list_iterator_current(iter);
    CU_ASSERT_EQUAL(current_value.i, value_1.i);
    ioopm_list_iterator_remove(iter);
    CU_ASSERT_EQUAL(ioopm_list_iterator_current(iter).i, value_2.i);
    ioopm_list_iterator_insert(iter, value_3);
    ioopm_list_iterator_insert(iter, value_4);
    ioopm_list_iterator_advance(iter);
    CU_ASSERT_EQUAL(ioopm_list_iterator_current(iter).i, value_4.i);
    ioopm_list_iterator_advance(iter);
    CU_ASSERT_EQUAL(ioopm_list_iterator_current(iter).i, value_3.i);
    ioopm_list_iterator_destroy(iter);
    ioopm_list_destroy(list);    

}


void test_create_empty_list()
{
    ioopm_list_t *list = ioopm_list_create();
    CU_ASSERT_TRUE(ioopm_list_is_empty(list));
    ioopm_list_destroy(list);
}
void test_append_list_once()
{
    elem_t value = int_elem(12);
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_append(list, value);
    elem_t head =ioopm_list_head(list);
    elem_t tail = ioopm_list_last(list);
    ioopm_list_destroy(list);
    CU_ASSERT_EQUAL(head.i, value.i);
    CU_ASSERT_EQUAL(tail.i, value.i);
}
void test_several_appends()
{
    elem_t value1 = int_elem(12);
    elem_t value2 = int_elem(13);
    elem_t value3 = int_elem(11);

    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, value1);
    ioopm_list_append(list, value2);
    ioopm_list_append(list, value3);

    size_t first_pos = 0;
    size_t middle_pos = 1;
    size_t last_pos = 2;

    elem_t head = ioopm_list_get(list, first_pos);
    elem_t middle = ioopm_list_get(list, middle_pos);
    elem_t tail = ioopm_list_get(list, last_pos);

    ioopm_list_destroy(list);

    CU_ASSERT_EQUAL(head.i, value1.i);
    CU_ASSERT_EQUAL(middle.i, value2.i);
    CU_ASSERT_EQUAL(tail.i, value3.i);
}

void test_several_prepends()
{
    elem_t value1 = int_elem(12);
    elem_t value2 = int_elem(13);
    elem_t value3 = int_elem(11);

    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_prepend(list, value1);
    ioopm_list_prepend(list, value2);
    ioopm_list_prepend(list, value3);

    size_t middle_pos = 1;

    elem_t head = ioopm_list_head(list);
    elem_t middle = ioopm_list_get(list, middle_pos);
    elem_t tail = ioopm_list_last(list);

    ioopm_list_destroy(list);

    CU_ASSERT_EQUAL(tail.i, value1.i);
    CU_ASSERT_EQUAL(middle.i, value2.i);
    CU_ASSERT_EQUAL(head.i, value3.i);
}

void test_append_prepend_insert()
{
    elem_t value1 = int_elem(12); // appendas sist
    elem_t value2 = int_elem(13); // prependas först
    elem_t value3 = int_elem(7);  // insertas i mitten

    ioopm_list_t *list = ioopm_list_create();

    size_t first_pos = 0;
    size_t middle_pos = 1;
    size_t last_pos = 2;

    ioopm_list_append(list, value1);                // list: [12]
    ioopm_list_prepend(list, value2);               // list: [13, 12]
    ioopm_list_insert(list, middle_pos, value3);    // list: [13, 7, 12]

    elem_t first = ioopm_list_get(list, first_pos);
    elem_t middle = ioopm_list_get(list, middle_pos);
    elem_t last = ioopm_list_get(list, last_pos);

    elem_t head = ioopm_list_head(list);
    elem_t tail = ioopm_list_last(list);

    ioopm_list_destroy(list);

    CU_ASSERT_EQUAL(first.i, value2.i);
    CU_ASSERT_EQUAL(middle.i, value3.i);
    CU_ASSERT_EQUAL(last.i, value1.i);

    CU_ASSERT_EQUAL(head.i, value2.i);
    CU_ASSERT_EQUAL(tail.i, value1.i);
}

void test_remove_from_list()
{
    elem_t value1 = int_elem(12);
    elem_t value2 = int_elem(13);
    elem_t value3 = int_elem(11);

    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, value1);
    ioopm_list_append(list, value2);
    ioopm_list_append(list, value3);
    // list: [12, 13, 11]

    size_t middle_pos = 1;
    elem_t removed = ioopm_list_remove(list, middle_pos); // ta bort mittenelementet
    // list: [12, 11]

    elem_t head = ioopm_list_head(list);
    elem_t tail = ioopm_list_last(list);
    size_t size = ioopm_list_size(list);

    ioopm_list_destroy(list);

    CU_ASSERT_EQUAL(removed.i, value2.i);
    CU_ASSERT_EQUAL(head.i, value1.i);
    CU_ASSERT_EQUAL(tail.i, value3.i);
    CU_ASSERT_EQUAL(size, 2);
}

void test_remove_first_and_last()
{
    elem_t value1 = int_elem(1);
    elem_t value2 = int_elem(2);
    elem_t value3 = int_elem(3);

    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, value1);
    ioopm_list_append(list, value2);
    ioopm_list_append(list, value3);
    // list: [1, 2, 3]

    size_t first_pos = 0;
    elem_t removed_first = ioopm_list_remove(list, first_pos);
    // list: [2, 3]

    size_t last_pos = ioopm_list_size(list) - 1;
    elem_t removed_last = ioopm_list_remove(list, last_pos);
    // list: [2]

    elem_t only_element = ioopm_list_head(list);
    size_t size = ioopm_list_size(list);

    ioopm_list_destroy(list);

    CU_ASSERT_EQUAL(removed_first.i, value1.i);
    CU_ASSERT_EQUAL(removed_last.i, value3.i);
    CU_ASSERT_EQUAL(only_element.i, value2.i);
    CU_ASSERT_EQUAL(size, 1);
}

void test_several_appends_string()
{
    elem_t value1 = string_elem("apple");
    elem_t value2 = string_elem("banana");
    elem_t value3 = string_elem("cherry");

    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, value1);
    ioopm_list_append(list, value2);
    ioopm_list_append(list, value3);

    size_t first_pos = 0;
    size_t middle_pos = 1;
    size_t last_pos = 2;

    elem_t head = ioopm_list_get(list, first_pos);
    elem_t middle = ioopm_list_get(list, middle_pos);
    elem_t tail = ioopm_list_get(list, last_pos);

    ioopm_list_destroy(list);

    CU_ASSERT_STRING_EQUAL(head.s, value1.s);
    CU_ASSERT_STRING_EQUAL(middle.s, value2.s);
    CU_ASSERT_STRING_EQUAL(tail.s, value3.s);
}

void test_several_prepends_string()
{
    elem_t value1 = string_elem("apple");
    elem_t value2 = string_elem("banana");
    elem_t value3 = string_elem("cherry");

    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_prepend(list, value1);
    ioopm_list_prepend(list, value2);
    ioopm_list_prepend(list, value3);
    // list: ["cherry", "banana", "apple"]

    size_t middle_pos = 1;

    elem_t head = ioopm_list_head(list);
    elem_t middle = ioopm_list_get(list, middle_pos);
    elem_t tail = ioopm_list_last(list);

    ioopm_list_destroy(list);

    CU_ASSERT_STRING_EQUAL(tail.s, value1.s);
    CU_ASSERT_STRING_EQUAL(middle.s, value2.s);
    CU_ASSERT_STRING_EQUAL(head.s, value3.s);
}

void test_append_prepend_insert_string()
{
    elem_t value1 = string_elem("last");    // appendas sist
    elem_t value2 = string_elem("first");   // prependas först
    elem_t value3 = string_elem("middle");  // insertas i mitten

    ioopm_list_t *list = ioopm_list_create();

    size_t first_pos = 0;
    size_t middle_pos = 1;
    size_t last_pos = 2;

    ioopm_list_append(list, value1);             // ["last"]
    ioopm_list_prepend(list, value2);            // ["first", "last"]
    ioopm_list_insert(list, middle_pos, value3); // ["first", "middle", "last"]

    elem_t first = ioopm_list_get(list, first_pos);
    elem_t middle = ioopm_list_get(list, middle_pos);
    elem_t last = ioopm_list_get(list, last_pos);

    elem_t head = ioopm_list_head(list);
    elem_t tail = ioopm_list_last(list);

    ioopm_list_destroy(list);

    CU_ASSERT_STRING_EQUAL(first.s, value2.s);
    CU_ASSERT_STRING_EQUAL(middle.s, value3.s);
    CU_ASSERT_STRING_EQUAL(last.s, value1.s);

    CU_ASSERT_STRING_EQUAL(head.s, value2.s);
    CU_ASSERT_STRING_EQUAL(tail.s, value1.s);
}

void test_remove_from_list_string()
{
    elem_t value1 = string_elem("apple");
    elem_t value2 = string_elem("banana");
    elem_t value3 = string_elem("cherry");

    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, value1);
    ioopm_list_append(list, value2);
    ioopm_list_append(list, value3);
    // list: ["apple", "banana", "cherry"]

    size_t middle_pos = 1;
    elem_t removed = ioopm_list_remove(list, middle_pos);
    // list: ["apple", "cherry"]

    elem_t head = ioopm_list_head(list);
    elem_t tail = ioopm_list_last(list);
    size_t size = ioopm_list_size(list);

    ioopm_list_destroy(list);

    CU_ASSERT_STRING_EQUAL(removed.s, value2.s);
    CU_ASSERT_STRING_EQUAL(head.s, value1.s);
    CU_ASSERT_STRING_EQUAL(tail.s, value3.s);
    CU_ASSERT_EQUAL(size, 2);
}

void test_remove_first_and_last_string()
{
    elem_t value1 = string_elem("one");
    elem_t value2 = string_elem("two");
    elem_t value3 = string_elem("three");

    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, value1);
    ioopm_list_append(list, value2);
    ioopm_list_append(list, value3);
    // list: ["one", "two", "three"]

    size_t first_pos = 0;
    elem_t removed_first = ioopm_list_remove(list, first_pos);
    // list: ["two", "three"]

    size_t last_pos = ioopm_list_size(list) - 1;
    elem_t removed_last = ioopm_list_remove(list, last_pos);
    // list: ["two"]

    elem_t only_element = ioopm_list_head(list);
    size_t size = ioopm_list_size(list);

    ioopm_list_destroy(list);

    CU_ASSERT_STRING_EQUAL(removed_first.s, value1.s);
    CU_ASSERT_STRING_EQUAL(removed_last.s, value3.s);
    CU_ASSERT_STRING_EQUAL(only_element.s, value2.s);
    CU_ASSERT_EQUAL(size, 1);
}

void test_iter_on_list_string()
{
    elem_t value = string_elem("hello");
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);
    ioopm_list_iterator_insert(iter, value);
    elem_t current_value = ioopm_list_iterator_current(iter);
    CU_ASSERT_STRING_EQUAL(current_value.s, value.s);
    ioopm_list_iterator_destroy(iter);
    ioopm_list_destroy(list);
}

void test_iter_advance_string()
{
    elem_t value_1 = string_elem("hello");
    elem_t value_2 = string_elem("world");
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);
    ioopm_list_iterator_insert(iter, value_1);
    ioopm_list_iterator_insert(iter, value_2);
    elem_t first_value = ioopm_list_iterator_current(iter);
    ioopm_list_iterator_advance(iter);
    elem_t second_value = ioopm_list_iterator_current(iter);
    CU_ASSERT_STRING_EQUAL(first_value.s, value_1.s);
    CU_ASSERT_STRING_EQUAL(second_value.s, value_2.s);
    ioopm_list_iterator_destroy(iter);
    ioopm_list_destroy(list);
}

void test_iter_remove_and_insert_string()
{
    elem_t value_1 = string_elem("alpha");
    elem_t value_2 = string_elem("beta");
    elem_t value_3 = string_elem("gamma");
    elem_t value_4 = string_elem("delta");
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);
    ioopm_list_iterator_insert(iter, value_1);
    ioopm_list_iterator_insert(iter, value_2);
    elem_t current_value = ioopm_list_iterator_current(iter);
    CU_ASSERT_STRING_EQUAL(current_value.s, value_1.s);
    ioopm_list_iterator_remove(iter);
    CU_ASSERT_STRING_EQUAL(ioopm_list_iterator_current(iter).s, value_2.s);
    ioopm_list_iterator_insert(iter, value_3);
    ioopm_list_iterator_insert(iter, value_4);
    ioopm_list_iterator_advance(iter);
    CU_ASSERT_STRING_EQUAL(ioopm_list_iterator_current(iter).s, value_4.s);
    ioopm_list_iterator_advance(iter);
    CU_ASSERT_STRING_EQUAL(ioopm_list_iterator_current(iter).s, value_3.s);
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
    ((CU_add_test(my_test_suite, "Test empty list", test_create_empty_list) == NULL ||
    CU_add_test(my_test_suite, "TEST APPEND and head/tail", test_append_list_once) == NULL ||
    CU_add_test(my_test_suite, "TEST several appends", test_several_appends) == NULL ||
    CU_add_test(my_test_suite, "TEST several prepends", test_several_prepends) == NULL ||
    CU_add_test(my_test_suite, "TEST append, prepend and insert", test_append_prepend_insert) == NULL ||
    CU_add_test(my_test_suite, "TEST remove from middle", test_remove_from_list) == NULL ||
    CU_add_test(my_test_suite, "TEST remove first and last", test_remove_first_and_last) == NULL ||
    CU_add_test(my_test_suite, "Test iter on empty list", test_create_empty_it) == NULL ||
    CU_add_test(my_test_suite, "Test iter on list", test_iter_on_list) == NULL ||
    CU_add_test(my_test_suite, "Test iter advance", test_iter_advance) == NULL ||
    CU_add_test(my_test_suite, "Test iter remove and insert", test_iter_remove_and_insert) == NULL ||
        CU_add_test(my_test_suite, "TEST several appends (string)", test_several_appends_string) == NULL ||
    CU_add_test(my_test_suite, "TEST several prepends (string)", test_several_prepends_string) == NULL ||
    CU_add_test(my_test_suite, "TEST append, prepend and insert (string)", test_append_prepend_insert_string) == NULL ||
    CU_add_test(my_test_suite, "TEST remove from middle (string)", test_remove_from_list_string) == NULL ||
    CU_add_test(my_test_suite, "TEST remove first and last (string)", test_remove_first_and_last_string) == NULL ||
    CU_add_test(my_test_suite, "Test iter on list (string)", test_iter_on_list_string) == NULL ||
    CU_add_test(my_test_suite, "Test iter advance (string)", test_iter_advance_string) == NULL ||
    CU_add_test(my_test_suite, "Test iter remove and insert (string)", test_iter_remove_and_insert_string) == NULL)
    
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