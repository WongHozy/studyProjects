OBJS = add.o sub.o div.o
TARGET = main.out
CC = g++

$(TARGET):main.c libmymath.so
	$(CC) $^ -o $@
	echo "build main.out finish"
libmymath.so:$(OBJS)
	$(CC) -shared $^ -o $@
	echo "build libmymath.so finish"
add.o:add.c
	$(CC) -c -fpic $^ -o $@
	echo "build add.o finish"
div.o:div.c
	$(CC) -c -fpic $^ -o $@
	echo "build div.o finish"
sub.o:sub.c
	$(CC) -c -fpic $^ -o $@
	echo "build" $@ "finish"

.PHONY:clean
clean:
	rm $(OBJS) libmymath.so main.out

