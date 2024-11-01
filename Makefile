PROJECT_NAME := My_grep
CC := gcc
FLAGS := -Wall -Wextra -Werror -std=c11

.PHONY: all clean style $(PROJECT_NAME)

all: $(PROJECT_NAME)

$(PROJECT_NAME): $(PROJECT_NAME).c
	$(CC) $(FLAGS) $(PROJECT_NAME).c -o $(PROJECT_NAME)

clean:
	rm -f $(PROJECT_NAME)

style:
	clang-format -style=google -n *.c

test: $(PROJECT_NAME)
	@cp $(PROJECT_NAME) tests
	@cp $(PROJECT_NAME).* tests
	@cp Makefile tests
	@cd tests && bash test_func_grep.sh