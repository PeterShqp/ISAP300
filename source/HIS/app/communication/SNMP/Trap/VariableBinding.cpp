#ifndef VariableBinding_CPP
#define VariableBinding_CPP

#include "VariableBinding.h"
#include "SNMPPdu.h"
#include "SNMPDefine.h"
#include "OID.h"
//#include "uart.h"
VariableBinding::VariableBinding()
{
}
VariableBinding::VariableBinding(Variable *o,Variable *v)
{
	oid.cloneVariable(o);
	value.cloneVariable(v);
}
VariableBinding::~VariableBinding()
{
}


void VariableBinding::setOID(Variable *o)
{
	if(o == NULL) return;
	oid.cloneVariable(o);
	

}
Variable* VariableBinding::getOID()
{
	return &oid;
}
AllInOneVariable* VariableBinding::getAllinOneOID()
{
	return &oid;
}

void VariableBinding::setValue(Variable *v)
{
	if(v==NULL) return;
	value.cloneVariable(v);
}

Variable* VariableBinding::getValue()
{
	return &value;
}
AllInOneVariable* VariableBinding::getAllinOneValue()
{
	return &value;
}
int VariableBinding::getBerLength()
{
	int len = 0;
	if( oid.valid )
	{
		len +=  oid.getBerLength();
	}
	else
	{
		len+=2;
	}
	if(value.valid)
	{
		len +=  value.getBerLength();
	}
	else
	{
		len+=2;
	}
	return len;	
}
uint8 VariableBinding::encodeData(unsigned char *buf,int len)	//��PDU�л��buffer
{
	
	buf[0] = 0x30;
	int offset = 0;
	offset = SNMPPdu::encodeLength(&(buf[1]),len-1,getBerLength());//�ܳ���
	int point = offset+1;
	if( oid.valid == FALSE )
	{
		buf[point] = VT_OID;
		buf[point+1] = 0;
		point +=2;
	}
	else
	{
		offset = oid.encode(&(buf[point]),len-point);
		point += offset;
	}
	if( value.valid == FALSE)
	{
		buf[point] = VT_Null;
		buf[point+1] = 0;
		point +=2;
	}
	else
	{
		offset = value.encode(&(buf[point]),len-point);
		point += offset;
	}
	return (uint8)point;


}
#endif
