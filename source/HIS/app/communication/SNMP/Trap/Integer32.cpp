#ifndef Integer32_CPP
#define Integer32_CPP

#include "Integer32.h"
#include "Variable.h"
#include "SNMPPdu.h"
#include "SNMPDefine.h"
Integer32::Integer32()
	: Variable()
{
	syntax = VT_Integer32;
	value = 0;
}
Integer32::Integer32(uint32 v)
	: Variable()
{
	syntax = VT_Integer32;
	value = v;
}
Integer32::~Integer32()
{

}
int Integer32::getBerLength()
{
	int intsize = SNMPPdu::getInteger32BerLength(value);
	int lgth = SNMPPdu::getLengthBerLength(intsize);
	return (intsize+lgth+1); 
}

bool Integer32::decode(unsigned char *buf,int len,uint8 *offset)
{
	return SNMPPdu::decodeInteger32(buf,len,(uint32*)&value,offset) ;
}
int Integer32::encode(unsigned char *buf,int len)
{
	return SNMPPdu::encodeInteger32(buf,len,value,syntax);
}
bool Integer32::getInteger32Value(uint32 *val)
{
	*val = value;
	return true;
}

#endif

