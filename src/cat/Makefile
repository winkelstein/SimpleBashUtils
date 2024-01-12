CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11

SRC=s21_cat.c ../common/utils.c flags.c utils.c

TARGET=s21_cat

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $@

clean:
	rm -rf *.o $(TARGET)

rebuild: clean s21_cat 

format:
	clang-format -i *.c *.h ../common/*.h ../common/*.c

check-format:
	clang-format -n *.c *.h ../common/*.h ../common/*.c

check:
	cppcheck --enable=all --suppress=missingIncludeSystem $(SRC) ../grep/s21_grep.c ../common/utils.c ../grep/utils.c