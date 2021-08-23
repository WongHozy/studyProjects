path = $(shell pwd)

math.out:main.c libtest.a
	gcc $< -I $(path) -L $(path) -l test -o $@
libtest.a:add.o sub.o div.o
	ar -rcs $@ $^
add.o:add.c
	gcc -c $^
sub.o:sub.c
	gcc -c $^
div.o:div.c
	gcc -c $^

.PHONY:clean
clean:
	rm *.o *.a *.out
