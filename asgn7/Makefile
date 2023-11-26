CC = clang
BASICS = -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -Werror -pedantic
debug: CFLAGS = $(BASICS) -gdwarf-4
release: CFLAGS = $(BASICS)
EXEC = xd
EXEC2 = bad_xd

.PHONY: all debug release clean scan-build

all: debug

debug: $(EXEC) $(EXEC2)

release: $(EXEC) $(EXEC2)

$(EXEC): $(EXEC).o
	$(CC) $^ -o $@

$(EXEC2): $(EXEC2).o
	$(CC) $^ -o $@
%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXEC) $(EXEC).o $(EXEC2) $(EXEC2).o

format:
	clang-format -i --style=file *.[ch]

scan-build: clean
	scan-build --use-cc=clang make
