#ifndef __X04_REQUEST_H__
#define __X04_REQUEST_H__
#include "modbustype.h"

typedef enum{
	X04RequestIndexSlave = 0,
	X04RequestIndexFcode = 1,
	X04RequestIndexOffset0= 2,
	X04RequestIndexOffset1= 3,
	X04RequestIndexCount0 = 4,
	X04RequestIndexCount1 = 5,
	X04RequestIndexCrc0 = 6,
	X04RequestIndexCrc1 = 7,
	X04RequestIndexMax = 8
}X04RequestIndex;

typedef enum{
	X04RequestCountMin = 1,
	X04RequestCountMax = 125 
}X04RequestCountType;

typedef struct {
	uint8_t data[X04RequestIndexMax];
}X04RequestContext;

uint8_t X04RequestCheck(X04RequestContext*);
uint8_t X04RequestGetSlave(X04RequestContext*);
uint8_t X04RequestGetFcode(X04RequestContext*);
uint16_t X04RequestGetOffset(X04RequestContext*);
uint16_t X04RequestGetCount(X04RequestContext*);
uint16_t X04RequestCalcCrc(X04RequestContext*);
uint16_t X04RequestGetCrc(X04RequestContext*);
uint8_t  X04RequestGetLength(X04RequestContext*);

void X04RequestSetSlave(X04RequestContext*, uint8_t);
void X04RequestSetFcode(X04RequestContext*, uint8_t);
void X04RequestSetOffset(X04RequestContext*, uint16_t);
void X04RequestSetCount(X04RequestContext*, uint16_t);
void X04RequestSetCrc(X04RequestContext*, uint16_t);

void X04RequestShowContext(X04RequestContext*);

#endif//__X04_REQUEST_H__
