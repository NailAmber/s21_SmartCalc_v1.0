CFLAGS=-Wall -Werror -Wextra -std=c11
CFLAGS=-Wall -Werror -Wextra -O2 -pedantic -std=c11 -Wshadow -Wlogical-op -Wshift-overflow=2 \
			-Wduplicated-cond -Wcast-align -Wfloat-equal -Wconversion -Wcast-qual -D_GLIBCXX_DEBUG \
			-D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined \
			-fno-sanitize-recover -fstack-protector -fanalyzer

POSIX=-D_POSIX_C_SOURCE=200809L
TESTS=$(wildcard ./unit_tests/s21_*.c)

all: clean calculus.a
	gcc $(CFLAGS) $(POSIX) main.c calculus.a -o main -lm

clean:
	rm -rf *.a *.o *.gcno *.gcda unit_test main *.css *.html *.gcov

rebuild: clean all

calculus.a:
	gcc $(CFLAGS) $(POSIX) calculus.c helping_func.c stack_an_queue.c -c
	ar rc calculus.a calculus.o helping_func.o stack_an_queue.o
	ranlib calculus.a

test: clean
	# gcc $(CFLAGS) $(POSIX) $(TESTS) -c 
	# gcc $(CFLAGS) $(POSIX) -o unit_test s21_*.o s21_matrix.c s21_help_functions.c --coverage -lcheck
	chmod +x unit_test
	./unit_test

gcov_report: clean test
	gcov *.gcda
	gcovr
	gcovr --html-details -o report.html

format:
	clang-format -n *.c *.h

formati:
	clang-format -i *.c *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --suppress=constParameterPointer --std=c11 *.c *.h

valgrind:
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s  ./main