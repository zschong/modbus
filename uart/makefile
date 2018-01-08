ARCH := 
CC := $(ARCH)g++
SRC := $(wildcard *.c)
SRC += $(wildcard *.cpp)

all: comport.exe

comport.exe: $(SRC)
	$(CC) $+ -DTEST_COMPORT -o $@ 
clean:
	@rm -rv *.o *.exe
