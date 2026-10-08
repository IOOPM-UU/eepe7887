CC = gcc
FLAGS = -Wall -g --coverage
LCUNIT = -lcunit



HASH_OBJECTS=hash_table_test.o hash_table.o utils.o
HASH_HEADERS=hash_table.h utils.h hash_table_iterator.h

$(HASH_OBJECTS): $(HASH_HEADERS)

LINK_OBJECTS=link_test_combined.o linked_list.o
LINK_HEADERS=linked_list.h list_iterator.h common.h

$(LINK_OBJECTS):$(LINK_HEADERS)

FREQ_OBJECTS=freq_count.o hash_table.o linked_list.o utils.o hash_table_iterator.o

$(FREQ_OBJECTS): $(HASH_HEADERS)


%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@
	

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
	rm -f *.o hash_table_test link_test_combined freq_count *.gcda *.gcno *.gcov

.PHONY: run_all mem_all clean_all coverage_all


freq_count: $(FREQ_OBJECTS)
	$(CC) $(FLAGS) $^ -o $@

1k-words: freq_count
	./freq_count 1k-long-words.txt

10k-words: freq_count
	./freq_count 10k-words.txt

16k-words: freq_count
	./freq_count 16k-words.txt


hash_table_test: $(HASH_OBJECTS)
	$(CC) $(FLAGS) $^ -o $@ $(LCUNIT)

hash_test: hash_table_test
	./hash_table_test

hash_memtest: hash_table_test
	valgrind --leak-check=full ./hash_table_test

hash_coverage: hash_table_test
	./hash_table_test
	gcov -b -c -f hash_table.c

hash_clean:
	rm -f *.o hash_table_test *.gcda *.gcno *.gcov

.PHONY: hash_test hash_memtest hash_clean hash_coverage


link_test_combined: $(LINK_OBJECTS)
	$(CC) $(FLAGS) $^ -o $@ $(LCUNIT)

linked_test: link_test_combined
	./link_test_combined

linked_memtest: link_test_combined
	valgrind --leak-check=full ./link_test_combined

linked_coverage: link_test_combined
	./link_test_combined
	gcov -b -c -f linked_list.c

linked_clean:
	rm -f *.o link_test_combined *.gcda *.gcno *.gcov

.PHONY: linked_test linked_memtest linked_clean 
	