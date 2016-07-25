#ifndef Counter64_H
#define Counter64_H

#include "Variable.h"

class Counter64	:public  Variable
{
public:
	uint32 high;
	uint32 low;

public:
	Counter64(void);
	Counter64(uint32 h,uint32 l);
	virtual ~Counter64(void);

	
	virtual bool decode(unsigned char *buf,int len,uint8 *offset);

	virtual int encode(unsigned char *buf,int len);
	virtual int getBerLength();

	virtual bool getInteger64Value(uint32 *h,uint32 *l);

};
#endif

