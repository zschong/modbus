#ifndef __UART_H__
#define __UART_H__
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "accesstermios.h"

enum
{
	Mode_422 = 0,
	Mode_485 = 1,
	Mode_232 = 2,
};
#define TIOCSERMODE 0x5460

int uart_open(const char *path);
int uart_config(int fd, int baud, char parity, int bsize, int stop);
int uart_read(int fd, char *buf, int len);
int uart_write(int fd, const char *data, int len);
int uart_close(int fd);

#endif//__UART_H__
