#ifndef __MCONTEXT_H__
#define __MCONTEXT_H__
#include "modbuscontext.h"

class X03Request;
class X03Response;
class X10Request;
class X10Response;

class Mcontext
{
protected:
	MBContext context;

public:
	Mcontext(void);

public:
	void Init(void);
	void Push(unsigned char);	
	void SetMac(unsigned char);
	bool CheckRequest(void);
	bool CheckResponse(void);
	virtual uint8_t GetLength(void);
	virtual uint8_t GetFcode(void);
	X03Request& GetX03Request(void);
	X03Response& GetX03Response(void);
	X10Request& GetX10Request(void);
	X10Response& GetX10Response(void);
};
class X03Request: public Mcontext
{
public:
	bool Check(void);
public:
	uint8_t GetSlave(void);
	uint8_t GetFcode(void);
	uint16_t GetOffset(void);
	uint16_t GetCount(void);
	uint16_t CalcCrc(void);
	uint16_t GetCrc(void);
	uint8_t GetLength(void);
public:
	void SetSlave(uint8_t);
	void SetFcode(uint8_t);
	void SetOffset(uint16_t);
	void SetCount(uint16_t);
	void SetCrc(uint16_t);
};
class X03Response: public Mcontext
{
public:
	bool Check(void);
public:
	uint8_t GetSlave(void);
	uint8_t GetFcode(void);
	uint8_t GetBcount(void);
	uint16_t GetData(uint8_t);
	uint16_t CalcCrc(void);
	uint16_t GetCrc(void);
	uint8_t GetLength(void);
public:
	void SetSlave(uint8_t);
	void SetFcode(uint8_t);
	void SetBcount(uint8_t);
	void SetData(uint8_t, uint16_t);
	void SetCrc(uint16_t);
};
class X10Request: public Mcontext
{
public:
	bool Check(void);
public:
	uint8_t GetSlave(void);
	uint8_t GetFcode(void);
	uint16_t GetOffset(void);
	uint16_t GetCount(void);
	uint8_t GetBcount(void);
	uint16_t GetData(uint8_t);
	uint16_t CalcCrc(void);
	uint16_t GetCrc(void);
	uint8_t GetLength(void);
public:
	void SetSlave(uint8_t);
	void SetFcode(uint8_t);
	void SetOffset(uint16_t);
	void SetCount(uint16_t);
	void SetBcount(uint8_t);
	void SetData(uint8_t, uint16_t);
	void SetCrc(uint16_t);
};
class X10Response: public Mcontext
{
public:
	bool Check(void);
public:
	uint8_t GetSlave(void);
	uint8_t GetFcode(void);
	uint16_t GetOffset(void);
	uint16_t GetCount(void);
	uint16_t CalcCrc(void);
	uint16_t GetCrc(void);
	uint8_t GetLength(void);
public:
	void SetSlave(uint8_t);
	void SetFcode(uint8_t);
	void SetOffset(uint16_t);
	void SetCount(uint16_t);
	void SetCrc(uint16_t);
};

#endif//__MCONTEXT_H__
