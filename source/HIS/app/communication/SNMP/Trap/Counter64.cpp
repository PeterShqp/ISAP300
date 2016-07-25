#ifndef Counter64_CPP
#define Counter64_CPP

#include "Counter64.h"
#include "Variable.h"
#include "SNMPPdu.h"
#include "SNMPDefine.h"

Counter64::Counter64()
	: Variable()
{
	syntax = VT_Counter64;
	high = 0;
	low = 0;
}
Counter64::Counter64(uint32 h,uint32 l)
	: Variable()
{
	syntax = VT_Counter64;
	high = h;
	low = l;
}
Counter64::~Counter64()
{

}
bool Counter64::decode(unsigned char *buf,int len,uint8 *offset)
{
	return SNMPPdu::decodeInteger64(buf,len,&high,&low,offset) ;
}

int Counter64::encode(unsigned char *buf,int len)
{
	return SNMPPdu::encodeInteger64(buf,len,high,low,syntax);
}
int Counter64::getBerLength()
{
	int intsize = SNMPPdu::getInteger64BerLength(high,low);
	int lgth = SNMPPdu::getLengthBerLength(intsize);
	return (intsize+lgth+1); 
}
bool Counter64::getInteger64Value(uint32 *h,uint32 *l)
{
	*h = high;
	*l = low;
	return true;
}


#endif

