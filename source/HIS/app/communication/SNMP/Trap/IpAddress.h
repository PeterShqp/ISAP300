#ifndef IpAddress_H
#define IpAddress_H

#include "Variable.h"

class IpAddress	:public  Variable
{
public:
	uint8 value[4];

public:
	IpAddress(void);
	IpAddress(uint8* v);
	virtual ~IpAddress();

	
	virtual bool decode(unsigned char *buf,int len,uint8 *offset);
	virtual int encode(unsigned char *buf,int len);
	virtual int getBerLength();
	virtual unsigned char* getOctetStringValue(int *len);

};
#endif

