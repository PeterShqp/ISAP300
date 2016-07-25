#ifndef Gauge32_H
#define Gauge32_H

#include "Variable.h"

class Gauge32	:public  Variable
{
public:
	uint32 value;

public:
	Gauge32(void);
	Gauge32(uint32 v);
	virtual ~Gauge32(void);

	
	virtual bool decode(unsigned char *buf,int len,uint8 *offset);

	virtual int encode(unsigned char *buf,int len);
	virtual int getBerLength();

	virtual bool getInteger32Value(uint32 *value);

};
#endif

