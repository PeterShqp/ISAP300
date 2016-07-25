#ifndef Counter32_CPP
#define Counter32_CPP

#include "Counter32.h"
#include "Variable.h"
#include "SNMPPdu.h"
#include "SNMPDefine.h"
Counter32::Counter32()
	: Variable()
{
	syntax = VT_Counter32;
	value = 0;
}
Counter32::Counter32(uint32 v)
	: Variable()
{
	syntax = VT_Counter32;
	value = v;
}
Counter32::~Counter32()
{

}
bool Counter32::decode(unsigned char *buf,int len,uint8 *offset)
{
	return SNMPPdu::decodeUnsignedInteger32(buf,len,&value,offset) ;
}

int Counter32::encode(unsigned char *buf,int len)
{
	return SNMPPdu::encodeUnsignedInteger32(buf,len,value,syntax);
}
int Counter32::getBerLength()
{
	int intsize = SNMPPdu::getUnsignedInteger32BerLength(value);
	int lgth = SNMPPdu::getLengthBerLength(intsize);
	return (intsize+lgth+1); 
}
bool Counter32::getInteger32Value(uint32 *val)
{
	*val = value;
	return true;
}

#endif

