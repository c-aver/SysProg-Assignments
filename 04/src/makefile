CC = gcc
CFLAGS = -Wall -Wextra -Werror -ggdb
EXE = digitcompress
MAIN = encodemain
LIB = compress

.SUFFIXES:
.PHONY: all clean

all: $(EXE)

$(EXE): $(MAIN).o $(LIB).o
	$(CC) $(CFLAGS) -o $@ $^

$(MAIN).o: $(MAIN).c
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIB).o: $(LIB).c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o $(EXE)
