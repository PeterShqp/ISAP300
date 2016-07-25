#ifndef TimeTicks_H
#define TimeTicks_H
#include "Variable.h"

class TimeTicks	:public  Variable
{
public:
	uint32 value;

public:
	TimeTicks(void);
	TimeTicks(int v);
	virtual ~TimeTicks(void);

	
	virtual bool decode(unsigned char *buf,int len,uint8 *offset);

	virtual int encode(unsigned char *buf,int len);
	virtual int getBerLength();

	virtual bool getInteger32Value(uint32 *value);

};
#endif

