#ifndef __PACKET_H__
#define __PACKET_H__

/*
 *[type][cmd][auto][double][name]
 */
 typedef unsigned char uint8_t;
 typedef unsigned short uint16_t;
 typedef unsigned int  uint32_t;
 typedef unsigned long long uint64_t;

typedef enum
{
	VarGetType,
	VarSetType,
	VarGetInit,
	VarSetInit,
	VarGetValue,
	VarSoftValue,
	VarHardValue,
	VarGetManual,
	VarSetManual,
	VarGetRuntime,
	VarSetRuntime,
	VarGetThreshold,
	VarSetThreshold,
	VarSetListener,
	VarGetInputList,
	VarGetOutputList,
	VarGetValueList,
	BasicAddFile,
	BasicDelFile,
	BasicSetRun,
	BasicGetRun,
	BasicSetDebug,
	BasicCompile,
}CommandType;

typedef enum
{
	Auto   = 0,
	Manual = 1,
}AutoType;

typedef enum
{
	TypeIndex   = 0,
	GuidIndex0  = 1,
	GuidIndex1  = 2,
	GuidIndex2  = 3,
	GuidIndex3  = 4,
	GuidIndex4  = 5,
	GuidIndex5  = 6,
	GuidIndex6  = 7,
	GuidIndex7  = 8,
	ValueIndex0 = 9,
	ValueIndex1 = 10,
	ValueIndex2 = 11,
	ValueIndex3 = 12,
	ValueIndex4 = 13,
	ValueIndex5 = 14,
	ValueIndex6 = 15,
	ValueIndex7 = 16,
	LengthIndex = 49,
	NameIndex	= 50,
	MaxIndex	= 128,
}IndexEnumDef;

class Packet
{
protected:
	unsigned char buffer[MaxIndex+1];

public:
	Packet(void);

public:
	unsigned char* data(void);
	unsigned int   size(void);

public:
	unsigned char type(void);
	unsigned long long guid(void);
	const double  dvalue(void);
	unsigned int  uvalue(void);
	const char*   svalue(void);
	unsigned int  length(void);
	const char*	  name(void);

public:
	void type(unsigned char t);
	void guid(unsigned long long);
	void dvalue(const double &v);
	void uvalue(unsigned int v);
	bool svalue(const char *buf);
	bool name(const char *buf);
};

#endif//__PACKET_H__
