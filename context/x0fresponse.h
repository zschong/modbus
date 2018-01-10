#ifndef __X0f_RESPONSE_H__
#define __X0f_RESPONSE_H__
#include "modbustype.h"

typedef enum{
	X0fResponseIndexSlave = 0,
	X0fResponseIndexFcode = 1,
	X0fResponseIndexOffset0 = 2,
	X0fResponseIndexOffset1 = 3,
	X0fResponseIndexCount0 = 4,
	X0fResponseIndexCount1 = 5,
	X0fResponseIndexCrc0 = 6,
	X0fResponseIndexCrc1 = 7,
	X0fResponseIndexMax = 8,
}X0fResponseIndex;

typedef enum{
	X0fResponseCountMin = 1,
	X0fResponseCountMax = 2000 
}X0fResponseCountType;

typedef struct {
	uint8_t data[X0fResponseIndexMax];
}X0fResponseContext;

uint8_t X0fResponseCheck(X0fResponseContext*);
uint8_t X0fResponseGetSlave(X0fResponseContext*);
uint8_t X0fResponseGetFcode(X0fResponseContext*);
uint16_t X0fResponseGetOffset(X0fResponseContext*);
uint16_t X0fResponseGetCount(X0fResponseContext*);
uint16_t X0fResponseCalcCrc(X0fResponseContext*);
uint16_t X0fResponseGetCrc(X0fResponseContext*);
uint8_t X0fResponseGetLength(X0fResponseContext*);

void X0fResponseSetSlave(X0fResponseContext*, uint8_t);
void X0fResponseSetFcode(X0fResponseContext*, uint8_t);
void X0fResponseSetOffset(X0fResponseContext*, uint16_t);
void X0fResponseSetCount(X0fResponseContext*, uint16_t);
void X0fResponseSetCrc(X0fResponseContext*, uint16_t);

void X0fResponseShowContext(X0fResponseContext*);

#endif//__X0f_RESPONSE_H__
