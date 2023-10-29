CC = clang
BASICS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
LFLAGS = -lm
EXEC = calc
HEADERS = mathlib.h stack.h operators.h messages.h
OBJS = mathlib.o stack.o operators.o
TESTS = tests
GRAPHS = graphs

debug: CFLAGS = $(BASICS) -gdwarf-4
all: CFLAGS = $(BASICS)
tests: CFLAGS = $(BASICS)
graphs: CFLAGS = $(BASICS)

all: $(EXEC) $(TESTS) $(GRAPHS)
debug: $(EXEC)

$(EXEC): $(EXEC).o $(OBJS)
	$(CC) $^ $(LFLAGS) -o $@

$(TESTS): $(TESTS).o $(OBJS)
	$(CC) $^ $(LFLAGS) -o $@

$(GRAPHS): $(GRAPHS).o $(OBJS)
	$(CC) $^ $(LFLAGS) -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(EXEC) *.o
	rm -rf $(TESTS) *.o
	rm -rf $(GRAPHS) *.o
	rm -rf $(GRAPHS) *.csv

format: 
	clang-format -i -style=file *.[ch]

scan-build: clean
	scan-build --use-cc=clang make

.PHONY: all clean format scan-build tests graphs
