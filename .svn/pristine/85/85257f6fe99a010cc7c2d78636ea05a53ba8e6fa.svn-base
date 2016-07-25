#ifndef OctetString_H
#define OctetString_H
#include "Variable.h"
class OctetString	:public  Variable
{
public:
	//unsigned char *octetstring;
	uint32 strlength;
	
	uint8 cstString[MaxOctecLen];
	uint8 *chgString;
	
public:
	OctetString(void);
	OctetString(unsigned char *o,int len);
	virtual ~OctetString(void);
	static int getLengthFromBuf(unsigned char *buf,int len);
	virtual bool decode(unsigned char *buf,int len,uint8 *offset);
	virtual int encode(unsigned char *buf,int len);

	virtual int getBerLength();
	virtual unsigned char* getOctetStringValue(int *len);
	
};
#endif

