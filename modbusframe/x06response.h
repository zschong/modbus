#ifndef __X06_RESPONSE_H__
#define __X06_RESPONSE_H__
#include "modbustype.h"

typedef enum{
	X06ResponseIndexSlave = 0,
	X06ResponseIndexFcode = 1,
	X06ResponseIndexOffset0= 2,
	X06ResponseIndexOffset1= 3,
	X06ResponseIndexValue0 = 4,
	X06ResponseIndexValue1 = 5,
	X06ResponseIndexCrc0 = 6,
	X06ResponseIndexCrc1 = 7,
	X06ResponseIndexMax = 8
}X06ResponseIndex;

typedef struct {
	uint8_t data[X06ResponseIndexMax];
}X06ResponseContext;

uint8_t X06ResponseCheck(X06ResponseContext*);
uint8_t X06ResponseGetSlave(X06ResponseContext*);
uint8_t X06ResponseGetFcode(X06ResponseContext*);
uint16_t X06ResponseGetOffset(X06ResponseContext*);
uint16_t X06ResponseGetValue(X06ResponseContext*);
uint16_t X06ResponseCalcCrc(X06ResponseContext*);
uint16_t X06ResponseGetCrc(X06ResponseContext*);
uint8_t  X06ResponseGetLength(X06ResponseContext*);

void X06ResponseSetSlave(X06ResponseContext*, uint8_t);
void X06ResponseSetFcode(X06ResponseContext*, uint8_t);
void X06ResponseSetOffset(X06ResponseContext*, uint16_t);
void X06ResponseSetValue(X06ResponseContext*, uint16_t);
void X06ResponseSetCrc(X06ResponseContext*, uint16_t);

void X06ResponseShowContext(X06ResponseContext*);

#endif//__X06_RESPONSE_H__
