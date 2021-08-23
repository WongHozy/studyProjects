libso2.so:so2.o
	g++ $^ -shared -o $@
so2.o:so2.c
	g++ -c $^ -fpic -o $@

.PHONY:clean
clean:
	-rm so2.o libso2.so
