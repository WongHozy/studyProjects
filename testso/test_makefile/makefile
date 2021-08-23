
CC = g++
OBJ := test.o so1.o so2.o
TOP_DIR := $(PWD)
SO1_DIR := $(TOP_DIR)/so1
SO2_DIR := $(TOP_DIR)/so2
SUB_DIR := so1 so2 test

export CC OBJ TOP_DIR SO1_DIR SO2_DIR


# test.out:test.o
#	$(CC) $< -ldl -Wl,-rpath=. -o $@
#test.o:test.c
#	$(CC) -c $^

all:CHECKDIR $(SUB_DIR)

CHECKDIR:
	mkdir -p $(SUB_DIR)

$(SUB_DIR):ECHO
	make -C $@
ECHO:
	@echo $(SUB_DIR)
	@echo bigin compile

