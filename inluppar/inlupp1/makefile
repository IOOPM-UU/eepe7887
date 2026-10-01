CC = gcc
FLAGS = -Wall -g
LCUNIT = -lcunit

hash_table_test: hash_table_test.o hash_table.o utils.o
	$(CC) $^ -o $@ $(LCUNIT)

hash_table_test.o: hash_table_test.c hash_table.h utils.h hash_table_iterator.h
	$(CC) $(FLAGS) -c hash_table_test.c

hash_table.o: hash_table.c hash_table.h common.h hash_table_iterator.h
	$(CC) $(FLAGS) -c hash_table.c

utils.o: utils.c utils.h
	$(CC) $(FLAGS) -c utils.c

test: hash_table_test
	./hash_table_test

memtest: hash_table_test
	valgrind --leak-check=full ./hash_table_test

clean:
	rm -f *.o hash_table_test

.PHONY: test memtest clean