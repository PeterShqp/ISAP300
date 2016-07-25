#ifndef VariableBinding_H
#define VariableBinding_H
#include "EZ_types.h"
#include "Variable.h"
#include "OID.h"
#include "AllInOneVariable.h"

class VariableBinding
{
public:
	//Variable *oid;
	//Variable *value;
	
	AllInOneVariable oid;
	AllInOneVariable value;

public:
	VariableBinding(void);
	VariableBinding(Variable *o,Variable *v);
	virtual ~VariableBinding(void);
	
	
	void setOID(Variable *o);
	Variable* getOID();
	AllInOneVariable* getAllinOneOID();

	void setValue(Variable *v);
	Variable* getValue();
	AllInOneVariable* getAllinOneValue();

	int getBerLength();
	uint8 encodeData(unsigned char *buf,int len);	//��PDU�л��buffer

};
#endif
