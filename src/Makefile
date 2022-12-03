CC=gcc #-std=c11
BASIC_FLAGS=-Wall -Wextra -Werror 
LIBSOURCES=$(wildcard comparison/*.c conversion/*.c arithmetic/*.c another/*.c additional/*.c)
LIBOBJECTS=$(LIBSOURCES:.c=.o)
TESTSOURCES=tests/*.c
COVERAGE=--coverage
LIB=s21_decimal.a


all: test
	make -j gcov_report
	@mkdir tech_folder
	mv *.gcda *.gcno s21_decimal.a test.info ./tech_folder
	#open report/index.html
	
test: $(LIB)
	$(CC) $(BASIC_FLAGS) $(COVERAGE) $(TESTSOURCES) $(LIBSOURCES) -L. $(LIB) -lcheck `pkg-config --cflags --libs check`
	exec ./a.out
	
$(LIB): $(LIBOBJECTS)
	ar rc $(LIB) $^
	ranlib $(LIB)
	
clean:
	@rm -rf $(LIB)
	@find . -name '*.o' -type f -delete
	@rm -rf a.out
	@find . -name '*.gcno' -type f -delete
	@find . -name '*.gcda' -type f -delete
	@find . -name '*.info' -type f -delete
	@rm -rf report
	@rm -rf tech_folder
	@echo "all cleaned"

re: clean all

style:
	python3 ../materials/linters/cpplint.py --extensions=c,h *.h comparison/*.c conversion/*.c arithmetic/*.c another/*.c additional/*.c comparison/*.h conversion/*.h arithmetic/*.h another/*.h additional/*.h
	leaks -atExit -- ./a.out

gcov_report: $(LIB) test
	lcov -t "test" -o test.info -c -d . #--rc #lcov_branch_coverage=1
	genhtml -o report test.info #--rc #lcov_branch_coverage=1

.PHONY: all clean test $(LIB) gcov_report
