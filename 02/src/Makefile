CC=gcc
CFLAGS=-Wall -Wextra -ggdb
MF=Makefile

my_graph: my_graph.o my_mat.o
	$(CC) $(CFLAGS) -o $@ $^

my_graph.o: my_graph.c my_mat.h $(MF)
	$(CC) -c $(CFLAGS) -o $@ $<

my_mat.o: my_mat.c my_mat.h $(MF)
	$(CC) -c $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f *.o my_graph
