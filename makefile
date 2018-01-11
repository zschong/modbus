ARCH := powerpc-e300c3-linux-gnu-
CC := $(ARCH)g++
STRIP := $(ARCH)strip
CFLAGS := -Imodbusframe -Imodbusservice
CFLAGS += -Isocketservice -Isocket -Iuart
CFLAGS += -DTEST_MODBUS
SRC := $(wildcard uart/*.c)
SRC += $(wildcard socket/*.c)
SRC += $(wildcard modbusframe/*.c)
CPP := $(wildcard modbusservice/*.cpp)
CPP += $(wildcard socketservice/*.cpp)
CPP += $(wildcard socket/*.cpp)
CPP += $(wildcard uart/*.cpp)
COBJ:= $(patsubst %.c, %.o, $(SRC))
XOBJ:= $(patsubst %.cpp, %.o, $(CPP))
OBJ := $(COBJ) $(XOBJ)
TARGET:= modbus.exe

all: $(TARGET)
	@echo -n "\033[32;4m"
	@echo -n "$(STRIP) $(TARGET) => "
	@ls -sh $(TARGET)
	@echo -n "\033[0m"

modbus.exe: $(OBJ)
	@$(CC) $+ -o $@
	@$(STRIP) $@

.c.o:
	@$(CC) $(CFLAGS) -c $*.c -o $@
	@echo '$(CC) $*.c => $@'
.cpp.o:
	@$(CC) $(CFLAGS) -c $*.cpp -o $@
	@echo '$(CC) $*.cpp => $@'

clean:
	@rm -rfv $(OBJ) *.exe
