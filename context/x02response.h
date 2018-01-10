#ifndef __X02_RESPONSE_H__
#define __X02_RESPONSE_H__
#include "x02request.h"
#include "modbustype.h"


typedef enum{
	X02ResponseIndexSlave = 0,
	X02ResponseIndexFcode = 1,
	X02ResponseIndexBcount= 2,
	X02ResponseIndexData = 3,
}X02ResponseIndex;

typedef enum {
	X02ResponseBcountMin = (X02RequestCountMin / 8) + !!(X02RequestCountMin % 8),
	X02ResponseBcountMax = (X02RequestCountMax / 8) + !!(X02RequestCountMax % 8),
}X02ResponseBcountType;

typedef struct {
	uint8_t data[X02ResponseIndexData + X02ResponseBcountMax + 2];
}X02ResponseContext;

uint8_t X02ResponseCheck(X02ResponseContext*);
uint8_t X02ResponseGetSlave(X02ResponseContext*);
uint8_t X02ResponseGetFcode(X02ResponseContext*);
uint8_t X02ResponseGetBcount(X02ResponseContext*);
uint8_t X02ResponseGetCoil(X02ResponseContext*, uint16_t);
uint16_t X02ResponseCalcCrc(X02ResponseContext*);
uint16_t X02ResponseGetCrc(X02ResponseContext*);
uint8_t  X02ResponseGetLength(X02ResponseContext*);

void X02ResponseSetSlave(X02ResponseContext*, uint8_t);
void X02ResponseSetFcode(X02ResponseContext*, uint8_t);
void X02ResponseSetBcount(X02ResponseContext*, uint8_t);
void X02ResponseSetCoil(X02ResponseContext*, uint16_t, uint8_t);
void X02ResponseSetCrc(X02ResponseContext*, uint16_t);

void X02ResponseShowContext(X02ResponseContext*);

#endif//__X02_RESPONSE_H__
