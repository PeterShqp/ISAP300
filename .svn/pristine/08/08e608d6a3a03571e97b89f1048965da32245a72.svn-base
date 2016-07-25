#ifndef Counter32_H
#define Counter32_H

#include "Variable.h"

class Counter32	:public  Variable
{
public:
	uint32 value;

public:
	Counter32(void);
	Counter32(uint32 v);
	virtual ~Counter32(void);

	
	virtual bool decode(unsigned char *buf,int len,uint8 *offset);

	virtual int encode(unsigned char *buf,int len);
	virtual int getBerLength();

	virtual bool getInteger32Value(uint32 *value);

};
#endif

