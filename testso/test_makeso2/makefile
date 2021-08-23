
CC = g++
OBJ := test.o so1.o so2.o
TOP_DIR := $(PWD)
SO1_DIR := $(TOP_DIR)/so1
SO2_DIR := $(TOP_DIR)/so2
SUB_DIR := so1 so2

export CC OBJ TOP_DIR SO1_DIR SO2_DIR


test.out:test.o
	$(CC) $< -ldl -Wl,-rpath=. -o test.out
test.o:test.c
	$(CC) -c $<

.PHONY : clean
clean:
	-rm test.out test.o
