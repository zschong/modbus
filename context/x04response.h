#ifndef __X04_RESPONSE_H__
#define __X04_RESPONSE_H__
#include "x04request.h"
#include "modbustype.h"


typedef enum{
	X04ResponseIndexSlave = 0,
	X04ResponseIndexFcode = 1,
	X04ResponseIndexBcount= 2,
	X04ResponseIndexData = 3,
}X04ResponseIndex;

typedef enum {
	X04ResponseBcountMin = X04RequestCountMin * 2,
	X04ResponseBcountMax = X04RequestCountMax * 2,
}X04ResponseBcountType;

typedef struct {
	uint8_t data[X04ResponseIndexData + X04ResponseBcountMax + 2];
}X04ResponseContext;

uint8_t X04ResponseCheck(X04ResponseContext*);
uint8_t X04ResponseGetSlave(X04ResponseContext*);
uint8_t X04ResponseGetFcode(X04ResponseContext*);
uint8_t X04ResponseGetBcount(X04ResponseContext*);
uint16_t X04ResponseGetData(X04ResponseContext*, uint8_t);
uint16_t X04ResponseCalcCrc(X04ResponseContext*);
uint16_t X04ResponseGetCrc(X04ResponseContext*);
uint8_t  X04ResponseGetLength(X04ResponseContext*);

void X04ResponseSetSlave(X04ResponseContext*, uint8_t);
void X04ResponseSetFcode(X04ResponseContext*, uint8_t);
void X04ResponseSetBcount(X04ResponseContext*, uint8_t);
void X04ResponseSetData(X04ResponseContext*, uint8_t, uint16_t);
void X04ResponseSetCrc(X04ResponseContext*, uint16_t);

void X04ResponseShowContext(X04ResponseContext*);

#endif//__X04_RESPONSE_H__
