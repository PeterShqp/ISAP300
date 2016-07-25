#ifndef AllInOneVariable_CPP
#define AllInOneVariable_CPP

#include "AllInOneVariable.h"
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
#include "snmppdu.h"
#include "string.h"
#include <stdlib.h>

//extern "C"  {
//extern void AccessLED(uint32 OnOff);
//}


AllInOneVariable::AllInOneVariable()
{
	syntax = VT_Null;
	value = 0;
	valuelow = 0;
	
	length  = 0;	
	chgString = NULL;
	
	valid = FALSE;

}

AllInOneVariable::~AllInOneVariable()
{
	if(chgString != NULL) delete []chgString;
}

uint32 AllInOneVariable::cloneVariable(Variable* vb)
{
	if(vb == NULL) return FAILED;
	uint8 syt = vb->getSyntax();
	syntax = syt;


	switch(syt)
	{
	case VT_Integer32:
	case VT_Gauge32:
	case VT_Counter32:
	case VT_TimeTicks:
		vb->getInteger32Value(&value);
		break;
	case VT_Counter64:
		vb->getInteger64Value(&value,&valuelow);
		break;		
	case VT_OctetString:		
	case VT_IPAddress:
	{
		unsigned char* buf = vb->getOctetStringValue((int*)&length);
		if( (length & 0x80000000)!=0) return FAILED;
		if(length>=MaxOctecLen) 
		{
			if(chgString != NULL) delete []chgString;
			chgString = new uint8[length];
			for(uint32 i=0;i<length;i++)
			{
				chgString[i] = buf[i];
			}
		}
		else
		{
			for(uint32 i=0;i<length;i++)
			{
				cstString[i] = buf[i];
			}
			
		}
		break;	
	}	
	case VT_Null:
	case VT_NoSuchObject:
	case VT_NoSuchInstance:
	case VT_EndofMibView:
		break;
	case VT_OID:
	{
		length = vb->getOIDLength();
		if(length>=OIDMaxLen || length == 0) return FAILED;
		uint32* oid = vb->getOIDValue((int*)&length);
		for(uint32 i=0;i<length;i++)
		{
			Oid[i] = oid[i];
		}
		break;
	}
	default:
		syntax = 0;
		return FAILED;
	}
	valid = TRUE;
	return SUCCESS;
}
int AllInOneVariable::getBerLength()
{
	switch(syntax)
	{
	case VT_Integer32:
	{
		int intsize = SNMPPdu::getInteger32BerLength(value);
		int lgth = SNMPPdu::getLengthBerLength(intsize);
		return (intsize+lgth+1); 
	}
	case VT_Gauge32:
	case VT_Counter32:
	case VT_TimeTicks:
	{
		int intsize = SNMPPdu::getUnsignedInteger32BerLength(value);
		int lgth = SNMPPdu::getLengthBerLength(intsize);
		return (intsize+lgth+1); 
	}
	case VT_Counter64:
	{
		int intsize = SNMPPdu::getInteger64BerLength(value,valuelow);
		int lgth = SNMPPdu::getLengthBerLength(intsize);
		return (intsize+lgth+1); 
	}
	case VT_OctetString:		
	{
		if(length > 0)
			return length+1+SNMPPdu::getLengthBerLength(length);
		else return 2;
	}
	case VT_IPAddress:
	{
		return 6; 	
	}	
	case VT_Null:
	case VT_NoSuchObject:
	case VT_NoSuchInstance:
	case VT_EndofMibView:
		return 2;
	case VT_OID:
	{
		int size = SNMPPdu::getOIDBerLength(Oid,length);
		int lgth = SNMPPdu::getLengthBerLength(size);
		return (size+lgth+1);
	}
	
	}
	return 2;
}
int AllInOneVariable::encode(unsigned char *buf,int len)
{
	switch(syntax)
	{
	case VT_Integer32:
	{
		return SNMPPdu::encodeInteger32(buf,len,value,syntax);
	}
	case VT_Gauge32:
	case VT_Counter32:
	case VT_TimeTicks:
	{
		return SNMPPdu::encodeUnsignedInteger32(buf,len,value,syntax);
	}
	case VT_Counter64:
	{
		return SNMPPdu::encodeInteger64(buf,len,value,valuelow,syntax);
	}
	case VT_OctetString:		
	{
		if(length>=MaxOctecLen)
			return SNMPPdu::encodeOctetString(buf,len,chgString,length,syntax);
		else
			return SNMPPdu::encodeOctetString(buf,len,cstString,length,syntax);
	}
	case VT_IPAddress:
	{
		return SNMPPdu::encodeOctetString(buf,len,cstString,4,syntax);

	}	
	case VT_Null:
	case VT_NoSuchObject:
	case VT_NoSuchInstance:
	case VT_EndofMibView:
	{
		if(buf == NULL || len <2) return 0;
		buf[0] = syntax;
		buf[1] = 0x00;
		return 2;
	}
	case VT_OID:
	{
		return SNMPPdu::encodeOID(buf,len,Oid,length);
	}
	
	}
	return 0;
}

int AllInOneVariable::getLengthFromBuf(unsigned char *buf,int len)
{
	if(buf == NULL || len<=1) return -1;
	

	if(buf[0]!=VT_OctetString) return -1;

	uint8 os= 0;
	int length = SNMPPdu::decodeLength(&(buf[1]),len-1,&os);

	if(length<0 ) return -1;
	return length;

}
bool AllInOneVariable::decode(unsigned char* buf ,int len,uint8* offset)
{
	switch(syntax)
	{
	case VT_Integer32:
	{
		return SNMPPdu::decodeInteger32(buf,len,(uint32*)&value,offset) ;
	}
	case VT_Gauge32:
	case VT_Counter32:
	case VT_TimeTicks:
	{
		return SNMPPdu::decodeUnsignedInteger32(buf,len,&value,offset) ;
	}
	case VT_Counter64:
	{
		return SNMPPdu::decodeInteger64(buf,len,&value,&valuelow,offset) ;
	}
	case VT_OctetString:		
	{
		int lth = getLengthFromBuf(buf,len);
		if(lth<0) return false;
		if(lth == 0)
		{
			length = 0;		
	        *offset = 2;
		}
		else
		{
			if(lth>=MaxOctecLen)
			{
				if(chgString != NULL) delete []chgString;
				chgString = new uint8[lth];
				length = lth;
				if(!SNMPPdu::decodeOctetString(buf,len,chgString,&lth,offset) )
				{
					delete []chgString;
					chgString = (unsigned char *)NULL;
					length = 0;
			 		return false;
				}
			}
			else
			{
				length = lth;
				if(!SNMPPdu::decodeOctetString(buf,len,cstString,&lth,offset) )
				{
					length = 0;
			 		return false;
				}
			}			
		}
		return true;
	}
	case VT_IPAddress:
	{
		if(buf == NULL || len<=1) return false;
		if(buf[0]!=VT_IPAddress) return false;

		int lth = buf[1];
		if(lth<0) return false;
		if(lth != 4)
		{
			memset((void*)cstString,0,4);
		}
		else
		{
			if(!SNMPPdu::decodeOctetString(buf,len,cstString,&lth,offset) )
			{
				memset((void*)cstString,0,4);
			 	return false;
			}
		}
		return true;

	}	
	case VT_Null:
	case VT_NoSuchObject:
	case VT_NoSuchInstance:
	case VT_EndofMibView:
	{
		if(buf == NULL || len<=1) return false;

		if(buf[0] == VT_Null || buf[0] == VT_NoSuchObject
			||buf[0] == VT_NoSuchInstance || buf[0] == VT_EndofMibView)
		{
			syntax = buf[0];
			uint8 os= 0;
			int lth = SNMPPdu::decodeLength(&(buf[1]),len-1,&os);
			if(lth != 0 ) return false;		
			*offset = 2;
			return true;				
		}
	}
	case VT_OID:
	{
		uint32 value;
		int valuelen = 0;
		value = SNMPPdu::decodeOID(buf, len,&valuelen,offset,Oid,OIDMaxLen);
		if( value == SUCCESS )
		{
			length = valuelen;
			return true;	
		}
		else return false;
	}
	
	}
	return false;

}

bool AllInOneVariable::isEquals(Variable * vobj)
{
	int cmp = CompareTo(vobj);
	if(cmp == 0) return true;
	else return false;
}
int AllInOneVariable::CompareTo(Variable *vobj)
{
	switch(syntax)
	{
		case VT_OID:
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
			if(length<min) min = length;

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
				return 	(length - vobjlen);
			}
			else
			{
				return res;
			}			
		}
	}
	return 1;
}
bool AllInOneVariable::startWith(Variable *vobj)
{
	switch(syntax)
	{
		case VT_OID:
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
			if(vobjlen >length) return false;


			for (int i=0; i<vobjlen; i++) 
			{
				if (Oid[i] != vobjoid[i]) 
				{
					return false;	
		      	}
		    }
			return true;
		}
	}
	return false;
}
uint32* AllInOneVariable::getOIDValue(int *len)
{
	switch(syntax)
	{
		case VT_OID:
		{
			*len = length;
			return Oid;
		}
	}
	*len = 0;
	return NULL;
}

bool AllInOneVariable::getInteger32Value(uint32 *val)
{
	switch(syntax)
	{
		case VT_Integer32:
		case VT_Gauge32:
		case VT_Counter32:
		case VT_TimeTicks:
		{
			*val = value;
			return true;
		}
	}
	*val = 0;
	return false;
}
unsigned char* AllInOneVariable::getOctetStringValue(int *len)
{
	switch(syntax)
	{
		case VT_IPAddress:
		{
			*len = 4;
			return cstString;
		}
		case VT_OctetString:
		{
			*len = length;
			if(*len <=0) return NULL;
			else if(length>=MaxOctecLen) return chgString;
			else return cstString;
		}
	}
	*len = 0;
	return (uint8*)NULL;
}
bool AllInOneVariable::getInteger64Value(uint32 *h,uint32 *l)
{
	switch(syntax)
	{
		case VT_Counter64:
		{
			*h = value;
			*l = valuelow;
			return true;
		}
	}
	*h = 0;
	*l = 0;
	return false;
}
uint32 AllInOneVariable::getOIDIndexValue(uint32 endPos)
{
	switch(syntax)
	{
		case VT_OID:
		{
			if(length>0 && length >= endPos && endPos > 0 )
			{
				return Oid[length-endPos];
			}
		}
	}
	return 0xffffffff;
}
uint32 AllInOneVariable::getOIDLength()
{
	switch(syntax)
	{
		case VT_OID:
		{
			return length;
		}
	}
	return 0;
}


#endif
