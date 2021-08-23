main.out : main.o
	gcc -g -o main.out main.o -lm      # makefile中的命令，必须以Tab键开始
main.o : main.c
	gcc -g -c main.c
#	gcc -c main.c      可使用隐晦规则，make自动推导

.PHONY : clean
clean :
	-rm main.out main.o
