CC = clang
BASICS = -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -Werror -pedantic
debug: CFLAGS = $(BASICS) -gdwarf-4
release: CFLAGS = $(BASICS)
EXEC = huff
EXEC2 = dehuff
TESTS = $(TEST1) $(TEST2) $(TEST3) $(TEST4) 
TEST1 = bwtest
TEST2 = brtest
TEST3 = nodetest
TEST4 = pqtest
OBJS = bitwriter.o bitreader.o pq.o node.o

.PHONY: all debug release clean scan-build

all: debug

debug: $(EXEC) $(EXEC2) $(TESTS)

release: $(EXEC) $(EXEC2) $(TEST1) $(TEST2) $(TEST3) $(TEST4)

$(EXEC): $(EXEC).o $(OBJS)
	$(CC) $^ -o $@

$(EXEC2): $(EXEC2).o $(OBJS)
	$(CC) $^ -o $@

$(TEST1): $(TEST1).o $(OBJS)
	$(CC) $^ -o $@

$(TEST2): $(TEST2).o $(OBJS)
	$(CC) $^ -o $@

$(TEST3): $(TEST3).o $(OBJS)
	$(CC) $^ -o $@

$(TEST4): $(TEST4).o $(OBJS)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXEC) $(EXEC).o $(EXEC2) $(EXEC2).o $(TESTS) $(TESTS).o

format:
	clang-format -i --style=file *.[ch]

scan-build: clean
	scan-build --use-cc=clang make
