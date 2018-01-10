#ifndef __X05_REQUEST_H__
#define __X05_REQUEST_H__
#include "modbustype.h"

typedef enum{
	X05RequestIndexSlave = 0,
	X05RequestIndexFcode = 1,
	X05RequestIndexOffset0= 2,
	X05RequestIndexOffset1= 3,
	X05RequestIndexValue0 = 4,
	X05RequestIndexValue1 = 5,
	X05RequestIndexCrc0 = 6,
	X05RequestIndexCrc1 = 7,
	X05RequestIndexMax = 8
}X05RequestIndex;

typedef enum{
	X05RequestValueOff = 0x0000,
	X05RequestValueOn = 0xFF00 
}X05RequestValueType;

typedef struct {
	uint8_t data[X05RequestIndexMax];
}X05RequestContext;

uint8_t X05RequestCheck(X05RequestContext*);
uint8_t X05RequestGetSlave(X05RequestContext*);
uint8_t X05RequestGetFcode(X05RequestContext*);
uint16_t X05RequestGetOffset(X05RequestContext*);
uint16_t X05RequestGetValue(X05RequestContext*);
uint16_t X05RequestCalcCrc(X05RequestContext*);
uint16_t X05RequestGetCrc(X05RequestContext*);
uint8_t  X05RequestGetLength(X05RequestContext*);

void X05RequestSetSlave(X05RequestContext*, uint8_t);
void X05RequestSetFcode(X05RequestContext*, uint8_t);
void X05RequestSetOffset(X05RequestContext*, uint16_t);
void X05RequestSetValue(X05RequestContext*, uint16_t);
void X05RequestSetCrc(X05RequestContext*, uint16_t);

void X05RequestShowContext(X05RequestContext*);

#endif//__X05_REQUEST_H__
