#ifndef __X06_REQUEST_H__
#define __X06_REQUEST_H__
#include "modbustype.h"

typedef enum{
	X06RequestIndexSlave = 0,
	X06RequestIndexFcode = 1,
	X06RequestIndexOffset0= 2,
	X06RequestIndexOffset1= 3,
	X06RequestIndexValue0 = 4,
	X06RequestIndexValue1 = 5,
	X06RequestIndexCrc0 = 6,
	X06RequestIndexCrc1 = 7,
	X06RequestIndexMax = 8
}X06RequestIndex;

typedef struct {
	uint8_t data[X06RequestIndexMax];
}X06RequestContext;

uint8_t X06RequestCheck(X06RequestContext*);
uint8_t X06RequestGetSlave(X06RequestContext*);
uint8_t X06RequestGetFcode(X06RequestContext*);
uint16_t X06RequestGetOffset(X06RequestContext*);
uint16_t X06RequestGetValue(X06RequestContext*);
uint16_t X06RequestCalcCrc(X06RequestContext*);
uint16_t X06RequestGetCrc(X06RequestContext*);
uint8_t  X06RequestGetLength(X06RequestContext*);

void X06RequestSetSlave(X06RequestContext*, uint8_t);
void X06RequestSetFcode(X06RequestContext*, uint8_t);
void X06RequestSetOffset(X06RequestContext*, uint16_t);
void X06RequestSetValue(X06RequestContext*, uint16_t);
void X06RequestSetCrc(X06RequestContext*, uint16_t);

void X06RequestShowContext(X06RequestContext*);

#endif//__X06_REQUEST_H__
