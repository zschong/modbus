ARCH := powerpc-e300c3-linux-gnu-
CC := $(ARCH)g++
STRIP := $(ARCH)strip
CFLAGS := -Icontext -Iservice -Iuart -DTEST_MODBUS
SRC := $(wildcard uart/*.c)
SRC += $(wildcard context/*.c)
CPP := $(wildcard service/*.cpp)
CPP += $(wildcard uart/*.cpp)
COBJ:= $(patsubst %.c, %.o, $(SRC))
XOBJ:= $(patsubst %.cpp, %.o, $(CPP))
OBJ := $(COBJ) $(XOBJ)

modbus.exe: $(OBJ)
	@$(CC) $+ -o $@
	@$(STRIP) $@
	@ls -sh $@

.c.o:
	@$(CC) $(CFLAGS) -c $*.c -o $@
	@echo 'cc $*.c => $@'
.cpp.o:
	@$(CC) $(CFLAGS) -c $*.cpp -o $@
	@echo 'cc $*.cpp => $@'

clean:
	@rm -rfv $(OBJ) *.exe
