#ifndef OctetString_CPP
#define OctetString_CPP

#include "OctetString.h"
#include "Variable.h"
#include "SNMPPdu.h"
#include "SNMPDefine.h"

OctetString::OctetString()
	: Variable()
{
	syntax = VT_OctetString;
	chgString = (uint8 *)NULL;
	strlength = 0;
}
OctetString::OctetString(unsigned char *o,int len)
{
	syntax =VT_OctetString;
	if(o == NULL || len<=0)
	{
		chgString = (uint8 *)NULL;
		strlength = 0;
		return;
	}
	if(len>=MaxOctecLen)
	{
		chgString = new unsigned char[len];
		for(int i=0;i<len;i++)
		{
			chgString[i] = o[i];	
		}
	}
	else
	{
		for(int i=0;i<len;i++)
		{
			cstString[i] = o[i];	
		}
		chgString = (uint8 *)NULL;
	}
	
	strlength = len;
}
OctetString::~OctetString()
{
	if(chgString != NULL) delete []chgString;
}
int OctetString::getBerLength()
{
	if(strlength > 0)
		return strlength+1+SNMPPdu::getLengthBerLength(strlength);
	else return 2;
}

int OctetString::getLengthFromBuf(unsigned char *buf,int len)
{
	if(buf == NULL || len<=1) return -1;
	

	if(buf[0]!=VT_OctetString) return -1;

	uint8 os= 0;
	int length = SNMPPdu::decodeLength(&(buf[1]),len-1,&os);

	if(length<0 ) return -1;
	return length;

}
bool OctetString::decode(unsigned char *buf,int len,uint8 *offset)
{
	int lth = getLengthFromBuf(buf,len);
	if(lth<0) return false;
	if(lth == 0)
	{
		strlength = 0;		
        *offset = 2;
	}
	else
	{
		if(lth>=MaxOctecLen)
		{
			if(chgString != NULL) delete []chgString;
			chgString = new uint8[lth];
			strlength = lth;
			if(!SNMPPdu::decodeOctetString(buf,len,chgString,&lth,offset) )
			{
				delete []chgString;
				chgString = (unsigned char *)NULL;
				strlength = 0;
		 		return false;
			}
		}
		else
		{
			strlength = lth;
			if(!SNMPPdu::decodeOctetString(buf,len,cstString,&lth,offset) )
			{
				strlength = 0;
		 		return false;
			}
		}
		
	}

	return true;
}
int OctetString::encode(unsigned char *buf,int len)
{
	if(strlength>=MaxOctecLen)
		return SNMPPdu::encodeOctetString(buf,len,chgString,strlength,syntax);
	else
		return SNMPPdu::encodeOctetString(buf,len,cstString,strlength,syntax);
}

unsigned char* OctetString::getOctetStringValue(int *len)
{
	*len = strlength;
	if(*len <=0) return NULL;
	else if(strlength>=MaxOctecLen) return chgString;
	else return cstString;
}

#endif

