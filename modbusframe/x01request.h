#ifndef __X01_REQUEST_H__
#define __X01_REQUEST_H__
#include "modbustype.h"

typedef enum{
	X01RequestIndexSlave = 0,
	X01RequestIndexFcode = 1,
	X01RequestIndexOffset0= 2,
	X01RequestIndexOffset1= 3,
	X01RequestIndexCount0 = 4,
	X01RequestIndexCount1 = 5,
	X01RequestIndexCrc0 = 6,
	X01RequestIndexCrc1 = 7,
	X01RequestIndexMax = 8
}X01RequestIndex;

typedef enum{
	X01RequestCountMin = 1,
	X01RequestCountMax = 2000 
}X01RequestCountType;

typedef struct {
	uint8_t data[X01RequestIndexMax];
}X01RequestContext;

uint8_t X01RequestCheck(X01RequestContext*);
uint8_t X01RequestGetSlave(X01RequestContext*);
uint8_t X01RequestGetFcode(X01RequestContext*);
uint16_t X01RequestGetOffset(X01RequestContext*);
uint16_t X01RequestGetCount(X01RequestContext*);
uint16_t X01RequestCalcCrc(X01RequestContext*);
uint16_t X01RequestGetCrc(X01RequestContext*);
uint8_t  X01RequestGetLength(X01RequestContext*);

void X01RequestSetSlave(X01RequestContext*, uint8_t);
void X01RequestSetFcode(X01RequestContext*, uint8_t);
void X01RequestSetOffset(X01RequestContext*, uint16_t);
void X01RequestSetCount(X01RequestContext*, uint16_t);
void X01RequestSetCrc(X01RequestContext*, uint16_t);

void X01RequestShowContext(X01RequestContext*);

#endif//__X01_REQUEST_H__
