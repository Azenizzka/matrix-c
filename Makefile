CC = gcc -Wall -Wextra
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=med

SRCMODULES = s21_matrix.c utils.c
OBJMODULES = $(SRCMODULES:.c=.o)

CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -L. s21_matrix.a -lm `pkg-config --cflags --libs check`
	
TEST_EXEC = test
REPORT_DIR = ./report

all: clean s21_matrix.a test

s21_matrix.a: $(OBJMODULES)
	ar rcs $@ $^
	ranlib $@

test: clean s21_matrix.a
	$(CC) $(CFLAGS) --coverage main.c -o $(TEST_EXEC) $(SRCMODULES) $(LDFLAGS)
	./$(TEST_EXEC)

gcov_report: test
	lcov -t "$(TEST_EXEC)" --output-file report.info --capture -q --directory ./
	genhtml -o $(REPORT_DIR) report.info

valgrind: test
	CK_FORK=no valgrind --leak-check=full ./test
	valgrind ./test

leaks: test
	leaks --atExit ./test

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o *.a *.gcno *.gcda *.out $(REPORT_DIR)/ report.info $(TEST_EXEC)

format:
	clang-format -i --style=Google *.c *.h