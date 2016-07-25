#ifndef Integer32_H
#define Integer32_H

#include "Variable.h"

class Integer32	:public  Variable
{
public:
	uint32 value;

public:
	Integer32(void);
	Integer32(uint32 v);
	virtual ~Integer32();

	
	virtual bool decode(unsigned char *buf,int len,uint8 *offset);
	virtual int encode(unsigned char *buf,int len);
	virtual bool getInteger32Value(uint32 *value);

	virtual int getBerLength();
};
#endif

