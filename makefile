CC=gcc
CFLAGS=-Wall -g
TARGET=NoobHash
OBJECTS=MyHash.o

all: MyHash.o main.c
	$(CC) $(CFLAGS) $(OBJECTS) main.c -o $(TARGET) -lm

$(OBJECTS): MyHash.c
	$(CC) $(CFLAGS) -c MyHash.c -o $(OBJECTS)
clean:
	rm -f *~
	rm -f *.o
	rm $(TARGET)