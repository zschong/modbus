#ifndef __MCONTEXT_H__
#define __MCONTEXT_H__
#include "modbuscontext.h"

class X01Request;
class X02Request;
class X03Request;
class X04Request;
class X05Request;
class X06Request;
class X0fRequest;
class X10Request;

class X01Response;
class X02Response;
class X03Response;
class X04Response;
class X05Response;
class X06Response;
class X0fResponse;
class X10Response;

class Mcontext
{
protected:
	MBContext context;

public:
	Mcontext(void);

public:
	void Show(void);
	void Init(void);
	void Push(uint8_t);	
	void PushW(uint16_t);	
	void SetMaster(uint8_t);	
	void SetServiceFcode(uint8_t);	
	bool CheckRequest(void);
	bool CheckResponse(void);

	uint8_t GetMaster(void);
	uint8_t GetServiceFcode(void);

	virtual uint8_t* GetData(void);
	virtual uint8_t GetLength(void);
	virtual uint8_t GetFcode(void);

	X01Request& GetX01Request(void);
	X02Request& GetX02Request(void);
	X03Request& GetX03Request(void);
	X04Request& GetX04Request(void);
	X05Request& GetX05Request(void);
	X06Request& GetX06Request(void);
	X0fRequest& GetX0fRequest(void);
	X10Request& GetX10Request(void);

	X01Response& GetX01Response(void);
	X02Response& GetX02Response(void);
	X03Response& GetX03Response(void);
	X04Response& GetX04Response(void);
	X05Response& GetX05Response(void);
	X06Response& GetX06Response(void);
	X0fResponse& GetX0fResponse(void);
	X10Response& GetX10Response(void);
};

class X01Request: public Mcontext
{
public:
	bool Check(void);
public:
	uint8_t GetSlave(void);
	uint8_t GetFcode(void);
	uint16_t GetOffset(void);
	uint16_t GetCount(void);
	uint16_t GetBcount(void);
	uint16_t GetCoil(uint16_t);
	uint16_t CalcCrc(void);
	uint16_t GetCrc(void);
	uint8_t GetLength(void);
public:
	void SetSlave(uint8_t);
	void SetFcode(uint8_t);
	void SetOffset(uint16_t);
	void SetCount(uint16_t);
	void SetBcount(uint8_t);
	void SetCoil(uint16_t, uint8_t);
	void SetCrc(uint16_t);
};
class X02Request: public Mcontext
{
public:
	bool Check(void);
public:
	uint8_t GetSlave(void);
	uint8_t GetFcode(void);
	uint16_t GetOffset(void);
	uint16_t GetCount(void);
	uint16_t GetBcount(void);
	uint16_t GetCoil(uint16_t);
	uint16_t CalcCrc(void);
	uint16_t GetCrc(void);
	uint8_t GetLength(void);
public:
	void SetSlave(uint8_t);
	void SetFcode(uint8_t);
	void SetOffset(uint16_t);
	void SetCount(uint16_t);
	void SetBcount(uint8_t);
	void SetCoil(uint16_t, uint8_t);
	void SetCrc(uint16_t);
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
class X04Request: public Mcontext
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
class X05Request: public Mcontext
{
public:
	bool Check(void);
public:
	uint8_t GetSlave(void);
	uint8_t GetFcode(void);
	uint16_t GetOffset(void);
	uint16_t GetValue(void);
	uint16_t CalcCrc(void);
	uint16_t GetCrc(void);
	uint8_t GetLength(void);
public:
	void SetSlave(uint8_t);
	void SetFcode(uint8_t);
	void SetOffset(uint16_t);
	void SetValue(uint16_t);
	void SetCrc(uint16_t);
};
class X06Request: public Mcontext
{
public:
	bool Check(void);
public:
	uint8_t GetSlave(void);
	uint8_t GetFcode(void);
	uint16_t GetOffset(void);
	uint16_t GetValue(void);
	uint16_t CalcCrc(void);
	uint16_t GetCrc(void);
	uint8_t GetLength(void);
public:
	void SetSlave(uint8_t);
	void SetFcode(uint8_t);
	void SetOffset(uint16_t);
	void SetValue(uint16_t);
	void SetCrc(uint16_t);
};
class X0fRequest: public Mcontext
{
public:
	bool Check(void);
public:
	uint8_t GetSlave(void);
	uint8_t GetFcode(void);
	uint16_t GetOffset(void);
	uint16_t GetCount(void);
	uint16_t GetBcount(void);
	uint16_t GetCoil(uint16_t);
	uint16_t CalcCrc(void);
	uint16_t GetCrc(void);
	uint8_t GetLength(void);
public:
	void SetSlave(uint8_t);
	void SetFcode(uint8_t);
	void SetOffset(uint16_t);
	void SetCount(uint16_t);
	void SetBcount(uint8_t);
	void SetCoil(uint16_t, uint8_t);
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

class X01Response: public Mcontext
{
public:
	bool Check(void);
public:
	uint8_t GetSlave(void);
	uint8_t GetFcode(void);
	uint8_t GetBcount(void);
	uint16_t GetCoil(uint16_t);
	uint16_t CalcCrc(void);
	uint16_t GetCrc(void);
	uint8_t GetLength(void);
public:
	void SetSlave(uint8_t);
	void SetFcode(uint8_t);
	void SetBcount(uint8_t);
	void SetCoil(uint16_t, uint8_t);
	void SetCrc(uint16_t);
};
class X02Response: public Mcontext
{
public:
	bool Check(void);
public:
	uint8_t GetSlave(void);
	uint8_t GetFcode(void);
	uint8_t GetBcount(void);
	uint16_t GetCoil(uint16_t);
	uint16_t CalcCrc(void);
	uint16_t GetCrc(void);
	uint8_t GetLength(void);
public:
	void SetSlave(uint8_t);
	void SetFcode(uint8_t);
	void SetBcount(uint8_t);
	void SetCoil(uint16_t, uint8_t);
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
class X04Response: public Mcontext
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
class X05Response: public Mcontext
{
public:
	bool Check(void);
public:
	uint8_t GetSlave(void);
	uint8_t GetFcode(void);
	uint8_t GetOffset(void);
	uint16_t GetValue(void);
	uint16_t CalcCrc(void);
	uint16_t GetCrc(void);
	uint8_t GetLength(void);
public:
	void SetSlave(uint8_t);
	void SetFcode(uint8_t);
	void SetOffset(uint16_t);
	void SetValue(uint16_t);
	void SetCrc(uint16_t);
};
class X06Response: public Mcontext
{
public:
	bool Check(void);
public:
	uint8_t GetSlave(void);
	uint8_t GetFcode(void);
	uint8_t GetOffset(void);
	uint16_t GetValue(void);
	uint16_t CalcCrc(void);
	uint16_t GetCrc(void);
	uint8_t GetLength(void);
public:
	void SetSlave(uint8_t);
	void SetFcode(uint8_t);
	void SetOffset(uint16_t);
	void SetValue(uint16_t);
	void SetCrc(uint16_t);
};
class X0fResponse: public Mcontext
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
