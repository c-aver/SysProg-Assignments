CC = gcc
CCFLAGS = -Wall -Wextra -ggdb
NCH = NumClass.h
BC = basicClassification
ACL = advancedClassificationLoop
ACR = advancedClassificationRecursion
LL = libclassloops
LR = libclassrec

.PHONY: clean loops loopd recursives recuresived all
.SUFFIXES:

all: loops loopd recursives recursived mains maindloop maindrec

mains: main.o $(LR).a
	$(CC) $(CCFLAGS) -o $@ $^

maindloop: main.o $(LL).so
	$(CC) $(CCFLAGS) -o $@ $^

maindrec: main.o $(LR).so
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c $(NCH)
	$(CC) -c $(CCFLAGS) -o $@ $<

$(BC).o: $(BC).c $(NCH)
	$(CC) -c -fPIC $(CCFLAGS) -o $@ $<

loops: $(LL).a
$(LL).a: $(BC).o $(ACL).o
	ar rcs $@ $^

loopd: $(LL).so 
$(LL).so: $(BC).o $(ACL).o
	$(CC) -shared $(CCFLAGS) -o $@ $^

$(ACL).o: $(ACL).c $(NCH)
	$(CC) -c -fPIC $(CCFLAGS) -o $@ $<

recursives: $(LR).a
$(LR).a: $(BC).o $(ACR).o
	ar rcs $@ $^

recursived: $(LR).so
$(LR).so: $(BC).o $(ACR).o
	$(CC) -shared $(CCFLAGS) -o $@ $^

$(ACR).o: $(ACR).c $(NCH)
	$(CC) -c -fPIC $(CCFLAGS) -o $@ $<

clean:
	rm -f *.o *.a *.so mains maindloop maindrec
