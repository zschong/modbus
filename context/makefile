ARCH :=
AR := $(ARCH)ar
CC := $(ARCH)g++
SRC := $(wildcard *.c)
OBJ := $(patsubst %.c, %.o, $(SRC))
LIb := modbuscontext.a
TARGET := X01Request.exe X01Response.exe
TARGET += X02Request.exe X02Response.exe
TARGET += X03Request.exe X03Response.exe
TARGET += X04Request.exe X04Response.exe
TARGET += X05Request.exe X05Response.exe
TARGET += X06Request.exe X06Response.exe
TARGET += X0fRequest.exe X0fResponse.exe
TARGET += X10Request.exe X10Response.exe
TARGET += modbuscontext.exe

test: $(TARGET)
	@./X01Request.exe
	@./X01Response.exe
	@./X02Request.exe
	@./X02Response.exe
	@./X03Request.exe
	@./X03Response.exe
	@./X04Request.exe
	@./X04Response.exe
	@./X05Request.exe
	@./X05Response.exe
	@./X06Request.exe
	@./X06Response.exe
	@./X0fRequest.exe
	@./X0fResponse.exe
	@./X10Request.exe
	@./X10Response.exe
	@./modbuscontext.exe
X01Request.exe: $(SRC)
	$(CC) $+ -DTEST_X01REQUEST -o $@
X01Response.exe: $(SRC)
	$(CC) $+ -DTEST_X01RESPONSE -o $@
X02Request.exe: $(SRC)
	$(CC) $+ -DTEST_X02REQUEST -o $@
X02Response.exe: $(SRC)
	$(CC) $+ -DTEST_X02RESPONSE -o $@
X03Request.exe: $(SRC)
	$(CC) $+ -DTEST_X03REQUEST -o $@
X03Response.exe: $(SRC)
	$(CC) $+ -DTEST_X03RESPONSE -o $@
X04Request.exe: $(SRC)
	$(CC) $+ -DTEST_X04REQUEST -o $@
X04Response.exe: $(SRC)
	$(CC) $+ -DTEST_X04RESPONSE -o $@
X05Request.exe: $(SRC)
	$(CC) $+ -DTEST_X05REQUEST -o $@
X05Response.exe: $(SRC)
	$(CC) $+ -DTEST_X05RESPONSE -o $@
X06Request.exe: $(SRC)
	$(CC) $+ -DTEST_X06REQUEST -o $@
X06Response.exe: $(SRC)
	$(CC) $+ -DTEST_X06RESPONSE -o $@
X0fRequest.exe: $(SRC)
	$(CC) $+ -DTEST_X0fREQUEST -o $@
X0fResponse.exe: $(SRC)
	$(CC) $+ -DTEST_X0fRESPONSE -o $@
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
