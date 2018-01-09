#ifndef __CONTEXT_H__
#define __CONTEXT_H__
#include "x03request.h"
#include "x03response.h"
#include "x10request.h"
#include "x10response.h"

typedef enum {
	MBContextIndexSlave = 0,
	MBContextIndexFcode = 1,
}MBContextIndexType;

typedef enum {
	MBContextFcodeX03 = 0x03,
	MBContextFcodeX10 = 0x10,
}MBContextFcodeType;
typedef struct {
	uint8_t buffer[255];
	uint8_t index;
	uint8_t master;
}MBContext;

void MBContextInit(MBContext*);
void MBContextPush(MBContext*, uint8_t);
void MBContextSetMaster(MBContext*, uint8_t);
uint8_t MBContextCheckRequest(MBContext*);
uint8_t MBContextCheckResponse(MBContext*);
uint8_t MBContextGetLength(MBContext*);
uint8_t MBContextGetFcode(MBContext*);
X03RequestContext* MBContextGetX03RequestContext(MBContext*);
X03ResponseContext* MBContextGetX03ResponseContext(MBContext*);
X10RequestContext* MBContextGetX10RequestContext(MBContext*);
X10ResponseContext* MBContextGetX10ResponseContext(MBContext*);

#endif//__CONTEXT_H__
