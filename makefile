ARCH := 
ARCH := powerpc-e300c3-linux-gnu-
ARCH := arm-linux-
CC := $(ARCH)g++
AR := $(ARCH)ar
ARFLAG := -rc
STRIP := $(ARCH)strip
INCS := $(wildcard [a-y]*/*.h)
OBJS := $(patsubst %.c, %.o, $(wildcard [a-y]*/*.c))
OBJS += $(patsubst %.cpp, %.o, $(wildcard [a-y]*/*.cpp))
CFLAGS := $(patsubst %, -I%, $(shell find [a-y]* -type d))
LIB_TARGET := thislib.a
EXE_TARGET := service_server.exe
EXE_TARGET += service_client.exe
EXE_TARGET += modbus_server.exe
EXE_TARGET += data.cgi

fast_make:
	make -f makefile all -j8 

all: $(EXE_TARGET)
	@echo -n "\33[33m"
	@echo "$(STRIP) $(EXE_TARGET)"
	@echo -n "\33[0m"
	@echo -n "\33[32m"
	@ls -1sh $+ $(LIB_TARGET)
	@echo -n "\33[0m"

service_server.exe: ztest/service_server.cpp $(LIB_TARGET)
	@echo "$(CC) ztest/service_server.cpp => $@"
	@$(CC) $(CFLAGS) $+ -o $@
	@$(STRIP) $@
service_client.exe: ztest/service_client.cpp $(LIB_TARGET)
	@echo "$(CC) ztest/service_client.cpp => $@"
	@$(CC) $(CFLAGS) $+ -o $@
	@$(STRIP) $@
modbus_server.exe: ztest/modbus_server.cpp $(LIB_TARGET)
	@echo "$(CC) ztest/modbus_server.cpp => $@"
	@$(CC) $(CFLAGS) $+ -o $@
	@$(STRIP) $@
data.cgi: ztest/data.cpp $(LIB_TARGET)
	@echo "$(CC) ztest/data.cpp => $@"
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
