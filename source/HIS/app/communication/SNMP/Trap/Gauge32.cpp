#ifndef Gauge32_CPP
#define Gauge32_CPP

#include "Gauge32.h"
#include "Variable.h"
#include "SNMPPdu.h"
#include "SNMPDefine.h"
Gauge32::Gauge32()
	: Variable()
{
	syntax = VT_Gauge32;
	value = 0;
}
Gauge32::Gauge32(uint32 v)
	: Variable()
{
	syntax = VT_Gauge32;
	value = v;
}
Gauge32::~Gauge32()
{

}
bool Gauge32::decode(unsigned char *buf,int len,uint8 *offset)
{
	return SNMPPdu::decodeUnsignedInteger32(buf,len,&value,offset) ;
}

int Gauge32::encode(unsigned char *buf,int len)
{
	return SNMPPdu::encodeUnsignedInteger32(buf,len,value,syntax);
}
int Gauge32::getBerLength()
{
	int intsize = SNMPPdu::getUnsignedInteger32BerLength(value);
	int lgth = SNMPPdu::getLengthBerLength(intsize);
	return (intsize+lgth+1); 
}
bool Gauge32::getInteger32Value(uint32 *val)
{
	*val = value;
	return true;
}

#endif

