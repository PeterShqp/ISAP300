#ifndef Null_H
#define Null_H
#include "Variable.h"

class Null	:public  Variable
{
public:
//	const static uint8 VT_NoSuchObject = 0x80;
//	const static uint8 VT_NoSuchInstance = 0x81;
//	const static uint8 VT_EndofMibView = 0x82;

	
	Null(void);
	Null(uint8 syt);
	virtual ~Null(void);

	virtual int getBerLength();

	virtual bool decode(unsigned char *buf,int len,uint8 *offset);
	virtual int encode(unsigned char *buf,int len);
};
#endif
