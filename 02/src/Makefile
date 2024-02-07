CC=gcc
CFLAGS=-Wall -Wextra -ggdb
MF=Makefile

all: my_graph my_Knapsack

my_Knapsack: my_Knapsack.c
	$(CC) $(CFLAGS) -o $@ $^

my_graph: my_graph.o my_mat.o
	$(CC) $(CFLAGS) -o $@ $^

my_graph.o: my_graph.c my_mat.h $(MF)
	$(CC) -c $(CFLAGS) -o $@ $<

my_mat.o: my_mat.c my_mat.h $(MF)
	$(CC) -c $(CFLAGS) -o $@ $<

.PHONY: clean all
clean:
	rm -f *.o my_graph
