#ifndef TimeTicks_CPP
#define TimeTicks_CPP

#include "TimeTicks.h"
#include "Variable.h"
#include "SNMPPdu.h"
#include "SNMPDefine.h"
TimeTicks::TimeTicks()
	: Variable()
{
	syntax = VT_TimeTicks;
	value = 0;
}
TimeTicks::TimeTicks(int v)
{
	syntax = VT_TimeTicks;
	value = v;
}
TimeTicks::~TimeTicks()
{

}
bool TimeTicks::decode(unsigned char *buf,int len,uint8 *offset)
{
	return SNMPPdu::decodeUnsignedInteger32(buf,len,&value,offset) ;
}

int TimeTicks::encode(unsigned char *buf,int len)
{
	return SNMPPdu::encodeUnsignedInteger32(buf,len,value,syntax);
}
int TimeTicks::getBerLength()
{
	int intsize = SNMPPdu::getUnsignedInteger32BerLength(value);
	int lgth = SNMPPdu::getLengthBerLength(intsize);
	return (intsize+lgth+1); 
}
bool TimeTicks::getInteger32Value(uint32 *val)
{
	*val = value;
	return true;
}

#endif

