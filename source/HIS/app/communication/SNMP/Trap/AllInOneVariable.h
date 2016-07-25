#ifndef AllInOneVariable_H
#define AllInOneVariable_H

#include "Variable.h"

class AllInOneVariable : public Variable
{
public:
	uint32 valid;
	uint32 value;
	uint32 valuelow;
	
	uint32 length;	
	uint8 cstString[MaxOctecLen];
	uint8 *chgString;
	
	uint32 Oid[OIDMaxLen];

	
public:
	AllInOneVariable(void);
	virtual ~AllInOneVariable(void);
	virtual uint32 cloneVariable(Variable* vb);
	virtual int getBerLength();
	
	virtual int encode(unsigned char *buf,int len);

	virtual bool decode(unsigned char *buf,int len,uint8 *offset);
	int getLengthFromBuf(unsigned char *buf,int len);

	virtual bool isEquals(Variable *vobj);
	virtual int CompareTo(Variable *vobj);
	virtual bool startWith(Variable *vobj);


	virtual uint32* getOIDValue(int *len);
	virtual bool getInteger32Value(uint32 *value);
	virtual unsigned char* getOctetStringValue(int *len);
	virtual bool getInteger64Value(uint32 *high,uint32 *low);

	virtual uint32 getOIDIndexValue(uint32 endPos);
	virtual uint32 getOIDLength();


};
#endif
