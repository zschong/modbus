#ifndef __VARID_H__
#define __VARID_H__

class VarId
{
protected:
	int value;
public:
	VarId(void);
	VarId(int v);
public:
	void SetValue(int);
	int  GetValue(void);
public:
	unsigned char GetSlave(void);
	unsigned char GetFcode(void);
	unsigned short GetOffset(void);
public:
	void SetSlave(int slave);
	void SetFcode(int fcode);
	void SetOffset(int offset);
};

#endif//__VARID_H__
