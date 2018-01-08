ARCH :=
AR := $(ARCH)ar
CC := $(ARCH)g++
SRC := $(wildcard *.c)
OBJ := $(patsubst %.c, %.o, $(SRC))
LIb := modbuscontext.a
TARGET := X03Request.exe X03Response.exe
TARGET += X10Request.exe X10Response.exe
TARGET += modbuscontext.exe

test: $(TARGET)
	@./X03Request.exe
	@./X03Response.exe
	@./X10Request.exe
	@./X10Response.exe
	@./modbuscontext.exe
X03Request.exe: $(SRC)
	$(CC) $+ -DTEST_X03REQUEST -o $@
X03Response.exe: $(SRC)
	$(CC) $+ -DTEST_X03RESPONSE -o $@
X10Request.exe: $(SRC)
	$(CC) $+ -DTEST_X10REQUEST -o $@
X10Response.exe: $(SRC) 
	$(CC) $+ -DTEST_X10RESPONSE -o $@
modbuscontext.exe: $(SRC)
	$(CC) $+ -DTEST_CONTEXT -o $@
.c.o:$(wildcard *.h)
	$(CC) -c $*.c -o $*.o
clean:
	@rm -rvf *.exe *.o
