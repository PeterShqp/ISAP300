#ifndef Variable_CPP
#define Variable_CPP

#include "Variable.h"
#include "Null.h"
#include "Integer32.h"
#include "OID.h"
#include "OctetString.h"
#include "Timeticks.h"
#include "Gauge32.h"
#include "Counter32.h"
#include "Counter64.h"
#include "IpAddress.h"
#include "SNMPDefine.h"

#include <stdlib.h>

extern "C"  {
extern void AccessLED(uint32 OnOff);
}


Variable::Variable()
{
	syntax = VT_Integer32;

}
Variable::Variable(uint8 sy)
{
	syntax = sy;
}
Variable::~Variable()
{

}

uint8 Variable::getSyntax()
{
	return syntax;
}

uint8 Variable::getBERSyntax(unsigned char *buf,int len)
{
	if(buf == NULL || len<=0) return 0;
	int syt = buf[0] & 0xff;
	if(syt == VT_Integer32 || syt == VT_OctetString || syt == VT_Null || syt == VT_OID
		|| syt == VT_IPAddress || syt == VT_Counter32 || syt == VT_Gauge32 || syt == VT_TimeTicks
		|| syt == VT_Opaque || syt == VT_Counter64 || syt == VT_NoSuchObject || syt == VT_NoSuchInstance
		|| syt == VT_EndofMibView)
	{
		return (uint8)syt;
	}
	return 0;

}
Variable* Variable::createVariable(Variable *in)
{
	if(in == NULL) return NULL;
	uint8 syt = in->getSyntax();
	switch(syt)
	{
	case VT_Integer32:
		{
			uint32 iv=0;
			if( in->getInteger32Value(&iv))
			{ 	
				Integer32 *value = new Integer32(iv);	
				return (Variable*)value;
			}
			else return NULL;
		}
	case VT_Gauge32:
		{
			uint32 iv=0;
			if( in->getInteger32Value(&iv))
			{ 	
				Gauge32 *value = new Gauge32(iv);	
				return (Variable*)value;
			}
			else return NULL;
		}
	case VT_Counter32:
		{
			uint32 iv=0;
			if( in->getInteger32Value(&iv))
			{ 	
				Counter32 *value = new Counter32(iv);	
				return (Variable*)value;
			}
			else return NULL;
		}
	case VT_Counter64:
		{
			uint32 h=0;
			uint32 l=0;
			if( in->getInteger64Value(&h,&l))
			{ 	
				Counter64 *value = new Counter64(h,l);	
				return (Variable*)value;
			}
			else return NULL;
		}
	case VT_OctetString:
		{
			int len = 0;
			unsigned char *v = in->getOctetStringValue(&len);
			OctetString *value = new OctetString(v,len);
			return (Variable*)value;
		}
	case VT_IPAddress:
		{
			int len = 0;
			unsigned char *v = in->getOctetStringValue(&len);
			IpAddress *value = new IpAddress(v);
			return (Variable*)value;
		}
	case VT_Null:
	case VT_NoSuchObject:
	case VT_NoSuchInstance:
	case VT_EndofMibView:
		{
			Null *value = new Null(syt);
			return (Variable*)value;
		}
	case VT_OID:
		{
			int len = 0;
			uint32 *vl =in->getOIDValue(&len);
			if(len<0) return NULL;
			OID *value = new OID(vl,len);
			return (Variable*)value;
		}
	case VT_TimeTicks:
		{
			uint32 iv=0;
			if( in->getInteger32Value(&iv))
			{ 	
				TimeTicks *value = new TimeTicks(iv);	
				return (Variable*)value;
			}
			else return NULL;	
		}
	}
	return NULL;
}

Variable* Variable::createVariable(unsigned char *buf,int len,uint8 *offset)
{
	uint8 syt = getBERSyntax(buf,len);
	if(syt == 0) return NULL;
	switch(syt)
	{
	case VT_Integer32:
		{
			Integer32 *value = new Integer32();
			if( value->decode(buf,len,offset) )
				return (Variable*)value;
		}
		break;
	case VT_Gauge32:
		{
			Gauge32 *value = new Gauge32();
			if( value->decode(buf,len,offset) )
				return (Variable*)value;
		}
		break;
	case VT_Counter32:
		{
			Counter32 *value = new Counter32();
			if( value->decode(buf,len,offset) )
				return (Variable*)value;
		}
		break;
	case VT_Counter64:
		{
			Counter64 *value = new Counter64();
			if( value->decode(buf,len,offset) )
				return (Variable*)value;
		}
		break;
	case VT_OctetString:
		{
			OctetString *value = new OctetString();
			if( value->decode(buf,len,offset) )
				return (Variable*)value;
		}
		break;
	case VT_IPAddress:
		{
			IpAddress *value = new IpAddress();
			if( value->decode(buf,len,offset) )
				return (Variable*)value;
		}
		break;
	case VT_Null:
	case VT_NoSuchObject:
	case VT_NoSuchInstance:
	case VT_EndofMibView:
		{
			Null *value = new Null();
			if( value->decode(buf,len,offset) )
			{
				return (Variable*)value;
			}
		}
		break;
	case VT_OID:
		{
			OID *value = new OID();
			if( value->decode(buf,len,offset) )
			{
				return (Variable*)value;
			}
		}
		break;
	case VT_TimeTicks:
		{
			TimeTicks *value = new TimeTicks();
			if( value->decode(buf,len,offset) )
				return (Variable*)value;
		}
		break;
	}
	return NULL;
}
uint32 Variable::cloneVariable(Variable* vb)
{
	return FAILED;
}
int Variable::getBerLength()
{
	return 2;
}
bool Variable::decode(unsigned char* ,int,uint8* )
{
/*	uint8* i = offset;
	i = buf;
	int j = len;
*/	return false;

}
int Variable::encode(unsigned char* ,int )
{
	return 0;
}

bool Variable::isEquals(Variable *)
{
	return false;
}
int Variable::CompareTo(Variable *)
{
	return 1;
}
bool Variable::startWith(Variable *)
{
	return false;
}
uint32* Variable::getOIDValue(int *)
{
	return NULL;
}

bool Variable::getInteger32Value(uint32 *)
{
	return false;
}
unsigned char* Variable::getOctetStringValue(int *)
{
	return (uint8*)NULL;
}
bool Variable::getInteger64Value(uint32 *,uint32 *)
{
	return false;
}
uint32 Variable::getOIDIndexValue(uint32 )
{
	return 0xffffffff;
}
uint32 Variable::getOIDLength()
{
	return 0;
}


#endif
