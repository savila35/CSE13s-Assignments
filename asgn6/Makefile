CC=clang
BASICS= -Wall -Wextra -Wstrict-prototypes -Werror -pedantic
debug:   CFLAGS = $(BASICS) -gdwarf-4
release: CFLAGS= $(BASICS)
iotest: CFLAGS = $(BASICS) -gdwarf-4
LDFLAGS=-lm
IOTEST=iotest
EXEC=colorb
OBJS=io.o bmp.o

.PHONY: all debug release clean scan-build iotest

all: debug iotest

debug: $(EXEC)

release: $(EXEC)

$(EXEC): $(OBJS) $(EXEC).o
	$(CC) $^ $(LDFLAGS) -o $@ 

$(IOTEST): $(OBJS) $(IOTEST).o
	$(CC) $^ $(LDFLAGS) -o $@ 

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXEC) $(OBJS) $(EXEC).o $(IOTEST).o $(IOTEST)

format:
	clang-format -i --style=file *.[ch]

scan-build: clean
	scan-build --use-cc=clang make

