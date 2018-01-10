#ifndef __X05_RESPONSE_H__
#define __X05_RESPONSE_H__
#include "modbustype.h"

typedef enum{
	X05ResponseIndexSlave = 0,
	X05ResponseIndexFcode = 1,
	X05ResponseIndexOffset0= 2,
	X05ResponseIndexOffset1= 3,
	X05ResponseIndexValue0 = 4,
	X05ResponseIndexValue1 = 5,
	X05ResponseIndexCrc0 = 6,
	X05ResponseIndexCrc1 = 7,
	X05ResponseIndexMax = 8
}X05ResponseIndex;

typedef enum{
	X05ResponseValueOff = 0x0000,
	X05ResponseValueOn = 0xFF00 
}X05ResponseValueType;

typedef struct {
	uint8_t data[X05ResponseIndexMax];
}X05ResponseContext;

uint8_t X05ResponseCheck(X05ResponseContext*);
uint8_t X05ResponseGetSlave(X05ResponseContext*);
uint8_t X05ResponseGetFcode(X05ResponseContext*);
uint16_t X05ResponseGetOffset(X05ResponseContext*);
uint16_t X05ResponseGetValue(X05ResponseContext*);
uint16_t X05ResponseCalcCrc(X05ResponseContext*);
uint16_t X05ResponseGetCrc(X05ResponseContext*);
uint8_t  X05ResponseGetLength(X05ResponseContext*);

void X05ResponseSetSlave(X05ResponseContext*, uint8_t);
void X05ResponseSetFcode(X05ResponseContext*, uint8_t);
void X05ResponseSetOffset(X05ResponseContext*, uint16_t);
void X05ResponseSetValue(X05ResponseContext*, uint16_t);
void X05ResponseSetCrc(X05ResponseContext*, uint16_t);

void X05ResponseShowContext(X05ResponseContext*);

#endif//__X05_RESPONSE_H__
