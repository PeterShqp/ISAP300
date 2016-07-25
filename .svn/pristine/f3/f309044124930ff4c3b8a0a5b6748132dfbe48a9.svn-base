#ifndef OID_H
#define OID_H

#include "Variable.h"



class OID	:public  Variable
{
public:
	//uint32 *oid;
	uint32 Oid[OIDMaxLen];
	int oidlength;
public:
	OID(void);
	OID(uint32* o,int len);
	virtual ~OID(void);
	virtual bool decode(unsigned char *buf,int len,uint8 *offset);
	virtual int encode(unsigned char *buf,int len);

	virtual bool isEquals(Variable *vobj);
	virtual int CompareTo(Variable *vobj);
	virtual uint32* getOIDValue(int *len);
	virtual bool startWith(Variable *vobj);

	virtual int getBerLength();
	virtual uint32 getOIDIndexValue(uint32 endPos);
	virtual uint32 getOIDLength();
};
#endif
