#ifndef Variable_H
#define Variable_H
#include "EZ_types.h"
#define MaxOctecLen 64
#define OIDMaxLen 64

class Variable
{
public:
	uint8 syntax;
	Variable(void);
	Variable(uint8 sy);
	virtual ~Variable(void);
	virtual uint32 cloneVariable(Variable* vb);
	uint8 getSyntax();

	static uint8 getBERSyntax(unsigned char *buf,int len);

	static Variable* createVariable(unsigned char *buf,int len,uint8 *offset);
	static Variable* createVariable(Variable *in);
	virtual bool decode(unsigned char *buf,int len,uint8 *offset);
	virtual int encode(unsigned char *buf,int len);

	virtual bool isEquals(Variable *vobj);
	virtual int CompareTo(Variable *vobj);
	virtual bool startWith(Variable *vobj);

	virtual int getBerLength();

	virtual uint32* getOIDValue(int *len);
	virtual bool getInteger32Value(uint32 *value);
	virtual unsigned char* getOctetStringValue(int *len);
	virtual bool getInteger64Value(uint32 *high,uint32 *low);

	virtual uint32 getOIDIndexValue(uint32 endPos);
	virtual uint32 getOIDLength();


};
#endif
