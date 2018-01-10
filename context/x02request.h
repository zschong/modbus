#ifndef __X02_REQUEST_H__
#define __X02_REQUEST_H__
#include "modbustype.h"

typedef enum{
	X02RequestIndexSlave = 0,
	X02RequestIndexFcode = 1,
	X02RequestIndexOffset0= 2,
	X02RequestIndexOffset1= 3,
	X02RequestIndexCount0 = 4,
	X02RequestIndexCount1 = 5,
	X02RequestIndexCrc0 = 6,
	X02RequestIndexCrc1 = 7,
	X02RequestIndexMax = 8
}X02RequestIndex;

typedef enum{
	X02RequestCountMin = 1,
	X02RequestCountMax = 2000 
}X02RequestCountType;

typedef struct {
	uint8_t data[X02RequestIndexMax];
}X02RequestContext;

uint8_t X02RequestCheck(X02RequestContext*);
uint8_t X02RequestGetSlave(X02RequestContext*);
uint8_t X02RequestGetFcode(X02RequestContext*);
uint16_t X02RequestGetOffset(X02RequestContext*);
uint16_t X02RequestGetCount(X02RequestContext*);
uint16_t X02RequestCalcCrc(X02RequestContext*);
uint16_t X02RequestGetCrc(X02RequestContext*);
uint8_t  X02RequestGetLength(X02RequestContext*);

void X02RequestSetSlave(X02RequestContext*, uint8_t);
void X02RequestSetFcode(X02RequestContext*, uint8_t);
void X02RequestSetOffset(X02RequestContext*, uint16_t);
void X02RequestSetCount(X02RequestContext*, uint16_t);
void X02RequestSetCrc(X02RequestContext*, uint16_t);

void X02RequestShowContext(X02RequestContext*);

#endif//__X02_REQUEST_H__
