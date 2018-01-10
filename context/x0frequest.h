#ifndef __X0f_REQUEST_H__
#define __X0f_REQUEST_H__
#include "modbustype.h"

typedef enum{
	X0fRequestIndexSlave = 0,
	X0fRequestIndexFcode = 1,
	X0fRequestIndexOffset0 = 2,
	X0fRequestIndexOffset1 = 3,
	X0fRequestIndexCount0 = 4,
	X0fRequestIndexCount1 = 5,
	X0fRequestIndexBcount = 6,
	X0fRequestIndexData = 7,
}X0fRequestIndex;

typedef enum{
	X0fRequestCountMin = 1,
	X0fRequestCountMax = 2000 
}X0fRequestCountType;

typedef enum{
	X0fRequestBcountMin = (X0fRequestCountMin / 8) + !!(X0fRequestCountMin % 8),
	X0fRequestBcountMax = (X0fRequestCountMax / 8) + !!(X0fRequestCountMax % 8),
}X0fRequestBcountType;

typedef struct {
	uint8_t data[X0fRequestIndexData + X0fRequestBcountMax + 2];
}X0fRequestContext;

uint8_t X0fRequestCheck(X0fRequestContext*);
uint8_t X0fRequestGetSlave(X0fRequestContext*);
uint8_t X0fRequestGetFcode(X0fRequestContext*);
uint16_t X0fRequestGetOffset(X0fRequestContext*);
uint16_t X0fRequestGetCount(X0fRequestContext*);
uint8_t  X0fRequestGetBcount(X0fRequestContext*);
uint16_t X0fRequestGetCoil(X0fRequestContext*, uint16_t);
uint16_t X0fRequestCalcCrc(X0fRequestContext*);
uint16_t X0fRequestGetCrc(X0fRequestContext*);
uint8_t X0fRequestGetLength(X0fRequestContext*);

void X0fRequestSetSlave(X0fRequestContext*, uint8_t);
void X0fRequestSetFcode(X0fRequestContext*, uint8_t);
void X0fRequestSetOffset(X0fRequestContext*, uint16_t);
void X0fRequestSetCount(X0fRequestContext*, uint16_t);
void X0fRequestSetBcount(X0fRequestContext*, uint8_t);
void X0fRequestSetCoil(X0fRequestContext*, uint16_t, uint8_t);
void X0fRequestSetCrc(X0fRequestContext*, uint16_t);

void X0fRequestShowContext(X0fRequestContext*);

#endif//__X0f_REQUEST_H__
