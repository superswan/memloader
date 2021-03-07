# compiler options
CC= cc
CFLAGS =-Wall -Wextra -Wpedantic \
		-Wformat=2 -Wno-unused-parameter -Wshadow \
		-Wwrite-strings -Wstrict-prototypes -Wold-style-definition \
		-Wredundant-decls -Wnested-externs -Wmissing-include-dirs

# path macros
BIN_PATH := bin
SRC_PATH := src

# compile
memloader: $(SRC_PATH)/memelf.c 
	$(CC) -o $(BIN_PATH)/memloader $(SRC_PATH)/memelf.c

memloadern: $(SRC_PATH)/memloadn.c 
	$(CC) -o $(BIN_PATH)/memloadern $(SRC_PATH)/memloadn.c -l curl

