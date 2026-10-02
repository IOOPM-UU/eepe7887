CC = gcc
FLAGS = -Wall -g --coverage
LCUNIT = -lcunit

all_test: hash_table_test link_test_combined
	

run_all: all_test
	./hash_table_test
	./link_test_combined

mem_all:
	valgrind --leak-check=full ./hash_table_test 
	valgrind --leak-check=full ./link_test_combined

coverage_all: run_all
	gcov -b -c -f linked_list.c hash_table.c

clean_all:
	rm -f *.o hash_table_test link_test_combined *.gcda *.gcno *.gcov


hash_table_test: hash_table_test.o hash_table.o utils.o
	$(CC) $(FLAGS) $^ -o $@ $(LCUNIT)

hash_table_test.o: hash_table_test.c hash_table.h utils.h hash_table_iterator.h
	$(CC) $(FLAGS) -c hash_table_test.c

hash_table.o: hash_table.c hash_table.h common.h hash_table_iterator.h
	$(CC) $(FLAGS) -c hash_table.c

utils.o: utils.c utils.h
	$(CC) $(FLAGS) -c utils.c

hash_test: hash_table_test
	./hash_table_test

hash_memtest: hash_table_test
	valgrind --leak-check=full ./hash_table_test

hash_coverage: hash_table_test
	./hash_table_test
	gcov -b -c -f hash_table.c

hash_clean:
	rm -f *.o hash_table_test *.gcda *.gcno *.gcov

.PHONY: hash_test hash_memtest clean


link_test_combined: link_test_combined.o linked_list.o
	$(CC) $(FLAGS) $^ -o $@ $(LCUNIT)

link_test_combined.o: link_test_combined.c linked_list.h list_iterator.h 
	$(CC) $(FLAGS) -c link_test_combined.c

linked_list.o: linked_list.c linked_list.h list_iterator.h common.h
	$(CC) $(FLAGS) -c linked_list.c

linked_test: link_test_combined
	./link_test_combined

linked_memtest: link_test_combined
	valgrind --leak-check=full ./link_test_combined

linked_coverage: link_test_combined
	./link_test_combined
	gcov -b -c -f linked_list.c

linked_clean:
	rm -f *.o link_test_combined *.gcda *.gcno *.gcov

.PHONY: linked_test linked_memtest clean

