CC = clang
BASICS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
LFLAGS = -lm
EXEC = calc
HEADERS = mathlib.h stack.h operators.h
OBJS = mathlib.o stack.o operators.o
TESTS = test

debug: CFLAGS = $(BASICS) -gdwarf-4
all: CFLAGS = $(BASICS)

all: $(EXEC) $(TESTS)
debug: $(EXEC)

$(EXEC): $(EXEC).o $(OBJS)
	$(CC) $^ $(CFLAGS) -o $@

$(TESTS): $(TESTS).o $(OBJS)
	$(CC) $^ $(LFLAGS) -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(EXEC) *.o
	rm -rf $(TESTS) *.o

format: 
	clang-format -i -style=file *.[ch]

.PHONY: all clean format