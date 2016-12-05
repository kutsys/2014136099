CC = gcc

TARGET = exe

$(TARGET) : mtest.o foo.o boo.o bar.o
	$(CC) -o $(TARGET)  mtest.o foo.o boo.o bar.o

mtest.o : mtest.c
	$(CC) -g -c -o mtest.o mtest.c

foo.o : foo.c
	$(CC) -g -c -o foo.o foo.c

boo.o : boo.c
	$(CC) -g -c -o boo.o boo.c

bar.o : bar.c
	$(CC) -g -c -o bar.o bar.c

clean :
	rm *.o exe

