
test.out:test.o
	$(CC) $< -ldl -Wl,-rpath=. -o $@
test.o:test.c
	$(CC) -c $^

.PHONY:clean
clean:
	-rm test.out
