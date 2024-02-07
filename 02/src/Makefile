CC=gcc
CFLAGS=-Wall -Wextra -ggdb
MF=Makefile		# to recompile everything when makefile changes

# question 1 executable
Q1=my_graph
# question 1 library
Q1L=my_mat
# question 2 executable
Q2=my_Knapsack

all: $(Q1) $(Q2)

# compile directly from c to executable since it does not depend on other files
$(Q2): $(Q2).c
	$(CC) $(CFLAGS) -o $@ $^

$(Q1): $(Q1).o $(Q1L).o
	$(CC) $(CFLAGS) -o $@ $^

$(Q1).o: $(Q1).c $(Q1L).h $(MF)
	$(CC) -c $(CFLAGS) -o $@ $<

$(Q1L).o: $(Q1L).c $(Q1L).h $(MF)
	$(CC) -c $(CFLAGS) -o $@ $<

.PHONY: clean all
.SUFFIXES:

clean:
	rm -f *.o $(Q1) $(Q2)
