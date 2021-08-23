

libso1.so:so1.o
	g++ $^ -shared -o $@
so1.o:so1.c
	g++ -c $^ -fpic -o $@

.PHONY:clean
clean:
	-rm so1.o libso1.so
