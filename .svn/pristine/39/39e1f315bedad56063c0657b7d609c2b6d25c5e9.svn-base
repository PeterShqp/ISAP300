#ifndef Null_CPP
#define Null_CPP

#include "Null.h"
#include "SNMPPdu.h"
#include "SNMPDefine.h"

Null::Null()
	: Variable()
{
	syntax = VT_Null;
	
}
Null::Null(uint8 syt)
{
	syntax = syt;
}
Null::~Null()
{


}

int Null::getBerLength()
{
	return 2;
}
bool Null::decode(unsigned char *buf,int len,uint8 *offset)
{
	if(buf == NULL || len<=1) return false;

	if(buf[0] == VT_Null || buf[0] == VT_NoSuchObject
		||buf[0] == VT_NoSuchInstance || buf[0] == VT_EndofMibView)
	{
		syntax = buf[0];
		uint8 os= 0;
		int length = SNMPPdu::decodeLength(&(buf[1]),len-1,&os);
		if(length != 0 ) return false;
	
		*offset = 2;
		return true;
			
	}
	return false;
}
int Null::encode(unsigned char *buf,int len)
{
	if(buf == NULL || len <2) return 0;
	buf[0] = syntax;
	buf[1] = 0x00;
	return 2;
}
	
#endif
