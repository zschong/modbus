ARCH :=
CC := $(ARCH)g++
CFLAGS := -Icontext -Iservice -Iuart
SRC := $(wildcard uart/*.c)
SRC += $(wildcard context/*.c)
CPP := $(wildcard service/*.cpp)
COBJ:= $(patsubst %.c, %.o, $(SRC))
XOBJ:= $(patsubst %.cpp, %.o, $(CPP))
OBJ := $(COBJ) $(XOBJ)
all:$(OBJ)

.c.o:
	$(CC) $(CFLAGS) -c $*.c -o $@
.cpp.o:
	$(CC) $(CFLAGS) -c $*.cpp -o $@

clean:
	rm -rfv $(OBJ)
