ARCH := 
ARCH := powerpc-e300c3-linux-gnu-
CC := $(ARCH)g++
AR := $(ARCH)ar
ARFLAG := -rc
STRIP := $(ARCH)strip
CFLAGS := $(patsubst %, -I%, $(shell find [a-y]* -type d))
INCS := $(wildcard [a-y]*/*.h)
OBJS := $(patsubst %.c, %.o, $(wildcard [a-y]*/*.c))
OBJS += $(patsubst %.cpp, %.o, $(wildcard [a-y]*/*.cpp))
LIB_TARGET := thislib.a
EXE_TARGET := modbus.exe
EXE_TARGET += service_server.exe
EXE_TARGET += service_client.exe

all: $(EXE_TARGET)
	@echo -n "\033[33;4m"
	@echo "strip  {$+}"
	@echo -n "\33[0m\033[32m"
	@ls -1sh $+ $(LIB_TARGET)
	@echo -n "\033[0m"

modbus.exe: ztest/modbus.cpp $(LIB_TARGET)
	@$(CC) $(CFLAGS) $+ -o $@
	@$(STRIP) $@
service_server.exe: ztest/service_server.cpp $(LIB_TARGET)
	@$(CC) $(CFLAGS) $+ -o $@
	@$(STRIP) $@
service_client.exe: ztest/service_client.cpp $(LIB_TARGET)
	@$(CC) $(CFLAGS) $+ -o $@
	@$(STRIP) $@
thislib.a:$(OBJS)
	@$(AR) $(ARFLAG) $@ $+

.c.o: $(INCS)
	@$(CC) $(CFLAGS) -c $*.c -o $@
	@echo '$(CC) $*.c => $@'
.cpp.o: $(INCS)
	@$(CC) $(CFLAGS) -c $*.cpp -o $@
	@echo '$(CC) $*.cpp => $@'

clean:
	@rm -rfv $(OBJS) $(EXE_TARGET) $(LIB_TARGET)
