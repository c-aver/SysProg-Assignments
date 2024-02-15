CC=gcc
CFLAGS=-Wall -Wextra -ggdb
MAIN=Main
MF=Makefile
LIB=StrList

$(LIB): $(MAIN).o $(LIB).o
	$(CC) $(CFLAGS) -o $@ $^

$(MAIN).o: $(MAIN).c $(MF)
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIB).o: $(LIB).c $(MF)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm *.o $(LIB)

.SUFFIXES:
.PHONY: clean
