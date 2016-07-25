#ifndef IpAddress_CPP
#define IpAddress_CPP

#include "IpAddress.h"
#include "Variable.h"
#include "SNMPPdu.h"
#include "SNMPDefine.h"
#include <string.h>
IpAddress::IpAddress()
	: Variable()
{
	syntax = VT_IPAddress;
	memset((void*)value,0,4);
}
IpAddress::IpAddress(uint8 *v)
	: Variable()
{
	syntax = VT_IPAddress;
	if(v == NULL) memset((void*)value,0,4);
	else
	{
		for(int i=0;i<4;i++)
		{
			value[i] = v[i];
		}
	}
}
IpAddress::~IpAddress()
{
}
int IpAddress::getBerLength()
{
	return 6; 
}

bool IpAddress::decode(unsigned char *buf,int len,uint8 *offset)
{
	if(buf == NULL || len<=1) return false;
	if(buf[0]!=VT_IPAddress) return false;

	int lth = buf[1];
	if(lth<0) return false;
	if(lth != 4)
	{
		memset((void*)value,0,4);
	}
	else
	{
		if(!SNMPPdu::decodeOctetString(buf,len,(unsigned char*)value,&lth,offset) )
		{
			memset((void*)value,0,4);
		 	return false;
		}
	}
	return true;

}
int IpAddress::encode(unsigned char *buf,int len)
{
	return SNMPPdu::encodeOctetString(buf,len,(unsigned char*)value,4,syntax);
}

unsigned char* IpAddress::getOctetStringValue(int *len)
{
	*len = 4;
	return (unsigned char*)value;
}

#endif

