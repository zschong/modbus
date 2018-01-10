#ifndef __CONTEXT_H__
#define __CONTEXT_H__
#include "x01request.h"
#include "x01response.h"
#include "x02request.h"
#include "x02response.h"
#include "x03request.h"
#include "x03response.h"
#include "x04request.h"
#include "x04response.h"
#include "x05request.h"
#include "x05response.h"
#include "x06request.h"
#include "x06response.h"
#include "x0frequest.h"
#include "x0fresponse.h"
#include "x10request.h"
#include "x10response.h"

typedef enum {
	MBContextIndexSlave = 0,
	MBContextIndexFcode = 1,
}MBContextIndexType;

typedef enum {
	MBContextFcodeX01 = 0x01,
	MBContextFcodeX02 = 0x02,
	MBContextFcodeX03 = 0x03,
	MBContextFcodeX04 = 0x04,
	MBContextFcodeX05 = 0x05,
	MBContextFcodeX06 = 0x06,
	MBContextFcodeX0f = 0x0f,
	MBContextFcodeX10 = 0x10,
}MBContextFcodeType;
typedef struct {
	uint8_t buffer[255];
	uint8_t index;
	uint8_t master;
	uint8_t service_fcode;
}MBContext;

void MBContextInit(MBContext*);
void MBContextPush(MBContext*, uint8_t);
void MBContextSetMaster(MBContext*, uint8_t);
void MBContextSetServiceFcode(MBContext*, uint8_t);
uint8_t MBContextCheckRequest(MBContext*);
uint8_t MBContextCheckResponse(MBContext*);

uint8_t MBContextGetLength(MBContext*);
uint8_t MBContextGetFcode(MBContext*);

X01RequestContext* MBContextGetX01RequestContext(MBContext*);
X02RequestContext* MBContextGetX02RequestContext(MBContext*);
X03RequestContext* MBContextGetX03RequestContext(MBContext*);
X04RequestContext* MBContextGetX04RequestContext(MBContext*);
X05RequestContext* MBContextGetX05RequestContext(MBContext*);
X06RequestContext* MBContextGetX06RequestContext(MBContext*);
X0fRequestContext* MBContextGetX0fRequestContext(MBContext*);
X10RequestContext* MBContextGetX10RequestContext(MBContext*);

X01ResponseContext* MBContextGetX01ResponseContext(MBContext*);
X02ResponseContext* MBContextGetX02ResponseContext(MBContext*);
X03ResponseContext* MBContextGetX03ResponseContext(MBContext*);
X04ResponseContext* MBContextGetX04ResponseContext(MBContext*);
X05ResponseContext* MBContextGetX05ResponseContext(MBContext*);
X06ResponseContext* MBContextGetX06ResponseContext(MBContext*);
X0fResponseContext* MBContextGetX0fResponseContext(MBContext*);
X10ResponseContext* MBContextGetX10ResponseContext(MBContext*);

#endif//__CONTEXT_H__
