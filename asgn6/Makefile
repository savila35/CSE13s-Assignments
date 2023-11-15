CC=clang
BASICS= -Wall -Wextra -Wstrict-prototypes -Werror -pedantic
debug:   CFLAGS= $(BASICS) -gdwarf-4
release: CFLAGS= $(BASICS)
colorb: CFLAGS= $(BASICS)
iotest: CFLAGS=-Wall -Wextra -Wstrict-prototypes -Werror -pedantic
LDFLAGS=-lm

IOTEST=iotest
EXECBIN=colorb 
OBJS=io.o bmp.o

.PHONY: all debug release clean scan-build iotest

all: release iotest

debug: $(EXECBIN)

release: $(EXECBIN)

$(EXECBIN): $(OBJS) colorb.o 
	$(CC) $^ $(LDFLAGS) -o $@ 

$(IOTEST): $(OBJS) iotest.o
	$(CC) $^ $(LDFLAGS) -o $@ 

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXECBIN) $(OBJS)

format:
	clang-format -i --style=file *.[ch]

scan-build: clean
	scan-build --use-cc=clang make

