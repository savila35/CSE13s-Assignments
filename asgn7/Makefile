CC = clang
BASICS = -Wall -Wextra -Wstrict-prototypes -Werror -pedantic
debug: CFLAGS = $(BASICS) -gdwarf-4
release: CFLAGS = $(BASICS)
EXEC = xd

.PHONY: all debug release clean scan-build

all: debug

debug: $(EXEC)

release: $(EXEC)

$(EXEC): $(EXEC).o
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXEC) $(EXEC).o

format:
	clang-format -i --style=file *.[ch]

scan-build: clean
	scan-build --use-cc=clang make
