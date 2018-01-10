#ifndef __X01_RESPONSE_H__
#define __X01_RESPONSE_H__
#include "x01request.h"
#include "modbustype.h"


typedef enum{
	X01ResponseIndexSlave = 0,
	X01ResponseIndexFcode = 1,
	X01ResponseIndexBcount= 2,
	X01ResponseIndexData = 3,
}X01ResponseIndex;

typedef enum {
	X01ResponseBcountMin = (X01RequestCountMin / 8) + !!(X01RequestCountMin % 8),
	X01ResponseBcountMax = (X01RequestCountMax / 8) + !!(X01RequestCountMax % 8),
}X01ResponseBcountType;

typedef struct {
	uint8_t data[X01ResponseIndexData + X01ResponseBcountMax + 2];
}X01ResponseContext;

uint8_t X01ResponseCheck(X01ResponseContext*);
uint8_t X01ResponseGetSlave(X01ResponseContext*);
uint8_t X01ResponseGetFcode(X01ResponseContext*);
uint8_t X01ResponseGetBcount(X01ResponseContext*);
uint8_t X01ResponseGetCoil(X01ResponseContext*, uint16_t);
uint16_t X01ResponseCalcCrc(X01ResponseContext*);
uint16_t X01ResponseGetCrc(X01ResponseContext*);
uint8_t  X01ResponseGetLength(X01ResponseContext*);

void X01ResponseSetSlave(X01ResponseContext*, uint8_t);
void X01ResponseSetFcode(X01ResponseContext*, uint8_t);
void X01ResponseSetBcount(X01ResponseContext*, uint8_t);
void X01ResponseSetCoil(X01ResponseContext*, uint16_t, uint8_t);
void X01ResponseSetCrc(X01ResponseContext*, uint16_t);

void X01ResponseShowContext(X01ResponseContext*);

#endif//__X01_RESPONSE_H__
