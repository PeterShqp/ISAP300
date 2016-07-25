#ifndef OID_CPP
#define OID_CPP

#include "OID.h"
#include "Variable.h"
#include "SNMPPdu.h"
#include "SNMPDefine.h"

#include "string.h"
extern "C"  {

extern void sendUint32Value(uint32 Value);
}
OID::OID()
	: Variable()
{
	OID::syntax = VT_OID;
	memset((uint8*)Oid,0,OIDMaxLen);
	oidlength = 0;
}
OID::OID(uint32* o,int len)
	: Variable()
{
	syntax = VT_OID;
	if(o == NULL)
	{
		oidlength = 0;
		return;
	}
	for(int i=0;i<len;i++)
	{
		Oid[i] = o[i];	
	}
	oidlength = len;
}

OID::~OID()
{
}

bool OID::decode(unsigned char *buf,int len,uint8 *offset)
{

	uint32 value;
	int valuelen = 0;
	value = SNMPPdu::decodeOID(buf, len,&valuelen,offset,Oid,OIDMaxLen);
	if( value == SUCCESS )
	{
		oidlength = valuelen;
		return true;	
	}
	else return false;

}
int OID::getBerLength()
{
	int size = SNMPPdu::getOIDBerLength(Oid,oidlength);
	int lgth = SNMPPdu::getLengthBerLength(size);
	return (size+lgth+1);
}
bool OID::isEquals(Variable *vobj)
{
	int cmp = CompareTo(vobj);
	if(cmp == 0) return true;
	else return false;

}

int OID::CompareTo(Variable *vobj)
{
	if(vobj->syntax != VT_OID)
	{	
		return Variable::CompareTo(vobj);
	}
	uint32 *vobjoid;
	int vobjlen = 0;
	vobjoid = vobj->getOIDValue(&vobjlen);
	if(vobjlen<=0 || vobjoid == NULL)
	{
		return Variable::CompareTo(vobj);
	}
	int min = vobjlen;
	if(oidlength<min) min = oidlength;

	int res = 0;
	for (int i=0; i<min; i++) 
	{
		if (Oid[i] == vobjoid[i]) 
		{	
		  	continue;
      	}
		else if ((Oid[i] & 0xFFFFFFFFL) <
               (vobjoid[i] & 0xFFFFFFFFL)) 
		{
        	res =  -1;
			break;
      	}
      	else 
		{
        	res =  1;
			break;
      	}
    }
	if(res == 0)
	{
		return 	(oidlength - vobjlen);
	}
	else
	{
		return res;
	}
}
bool OID::startWith(Variable *vobj)
{
	if(vobj->syntax != VT_OID)
	{	
		return Variable::startWith(vobj);
	}
	uint32 *vobjoid;
	int vobjlen = 0;
	vobjoid = vobj->getOIDValue(&vobjlen);
	if(vobjlen<=0 || vobjoid == NULL)
	{
		return Variable::startWith(vobj);
	}
	if(vobjlen > oidlength) return false;


	for (int i=0; i<vobjlen; i++) 
	{
		if (Oid[i] != vobjoid[i]) 
		{
			return false;	
      	}
    }
	return true;
}
uint32* OID::getOIDValue(int *len)
{
	*len = oidlength;
	return Oid;
		
}

int OID::encode(unsigned char *buf,int len)
{
	return SNMPPdu::encodeOID(buf,len,Oid,oidlength);
}
uint32 OID::getOIDIndexValue(uint32 endPos)
{
	if(oidlength>0 && oidlength >= endPos && endPos > 0 )
	{
		return Oid[oidlength-endPos];
	}
	return 0xffffffff;
}
uint32 OID::getOIDLength()
{
	return oidlength;
}

#endif

