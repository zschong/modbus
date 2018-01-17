ARCH:=/usr/bin/
CC:=$(ARCH)g++
CFLAGS:= -I./ -I../
SRC:= unix-udp.cpp 

all: unix-udp-client.exe unix-udp-server.exe unix-udp-connect.exe

unix-udp-client.exe: $(SRC) test/unix-udp-client.cpp
	$(CC) $(CFLAGS) $+ -o $@

unix-udp-connect.exe: $(SRC) test/unix-udp-connect.cpp
	$(CC) $(CFLAGS) $+ -o $@

unix-udp-server.exe: $(SRC) test/unix-udp-server.cpp
	$(CC) $(CFLAGS) $+ -o $@

clean:
	@rm -vrf *.o *.exe 
	@unlink unixudp.udp.clien.socket
	@unlink unixudp.udp.server.socket
