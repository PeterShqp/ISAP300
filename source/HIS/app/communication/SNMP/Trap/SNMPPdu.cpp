#ifndef SNMPPdu_CPP
#define SNMPPdu_CPP

#include "SNMPPdu.h"
#include "Integer32.h"
#include "OctetString.h"
#include "Oid.h"
#include "string.h"
#include "SNMPDefine.h"

extern "C"  {
extern void AccessLED(uint32 OnOff);
}
uint16 rqid = 1;
SNMPPdu::SNMPPdu(void)
{
    version = SNMPPdu::version2c;						   	//�汾��ֻ֧��V2c��v1����ݰ���V2c��ʽ����
	cmtylen = 6;
	commond = SNMPPdu::GET;							//��ݰ�����
	requestID = rqid++;						//����ID
	if(rqid == 0) rqid = 1;
	errorStatus = SNMPPdu::SNMP_ERROR_SUCCESS;						//���״̬
	errorIndex = 0;						//�������
	isValid = true;
	memcpy(Community,"public",6);

}

SNMPPdu::SNMPPdu(unsigned char *buf,int len,VariableBinding* vbs,int vbsmemlen) //��buffer�л��PDU����
{
    version = SNMPPdu::version2c;						   	//�汾��ֻ֧��V2c��v1����ݰ���V2c��ʽ����
	cmtylen = 6;
	memcpy(Community,"public",6);
	commond = SNMPPdu::GET;							//��ݰ�����
	requestID = rqid++;						//����ID
	if(rqid == 0) rqid = 1;
	errorStatus = SNMPPdu::SNMP_ERROR_SUCCESS;						//���״̬
	errorIndex = 0;						//�������
	isValid = true;
	
	variableBindings.variableBinding = vbs;
	variableBindings.vbsmemsize = vbsmemlen;
	if( decodeData(buf,len) )
	{
		isValid	= true;
	}
	else
	{
		isValid	= false;
	}
}
SNMPPdu::~SNMPPdu(void)
{
	
	   
}						   				 
/*
	��buffer�������ȷ��SNMP Pdu
	buf:   PDU�Ļ���buffer
	len:   buffer���ó���
	����ֵ:	 ��ȷ���Pdu���־
*/				  
bool SNMPPdu::decodeData(unsigned char *buf,int len)	//��buffer�л��PDU
{


	if(buf == NULL || len<=0) return false;
	
	if(buf[0]!=0x30) return false;
	uint8 offset= 0;
	int pdulength = SNMPPdu::decodeLength(&(buf[1]),len-1,&offset);	  //�����ݰ�Ȳ�У��
	if(pdulength<0 || pdulength != len-1-offset) return false;
	int point = offset+1;
	if(point>=len) return false;
	uint32 value = 0;
	if( !SNMPPdu::decodeInteger32(&(buf[point]),len-point,&value,&offset) )  //��ȡ�汾
	{
		return false;
	}
	if(value == SNMPPdu::version1 || value == SNMPPdu::version2c) 	//ֻ����v1��v2c��snmp��ݰ�			 
	{
		version = value;
	}
	else
	{
		return false;
	}

	
	point += offset;
	if(point>=len) return false;
	int cmtlen = OctetString::getLengthFromBuf(&(buf[point]),len-point);  //���Community����
	if(cmtlen<0) return false;
	if(cmtlen == 0 )
	{
		point += 2;
		cmtylen = 0;
	}
	else if(cmtlen >= CommunityMaxLen)
	{
		return false;
	}
	else
	{
		if(!decodeOctetString(&(buf[point]),len-point,Community,&cmtlen,&offset) ) return false;
		cmtylen = cmtlen;
		point += offset;

	}
	if(point>=len) return false;

	//PDU����
	if(buf[point] == SNMPPdu::GET || buf[point] == SNMPPdu::SET || buf[point] == SNMPPdu::RESPONSE
	    ||buf[point] == SNMPPdu::TRAP || buf[point] == SNMPPdu::GETNEXT)
	{
		commond	= buf[point];
	}
	else
	{
		return false;
	}
	//if(!IsValidCommunity(Community,cmtylen,commond)) 	return false;//�Ƿ�����ȷ��Community
	point ++;
	if(point>=len) return false;
	pdulength = SNMPPdu::decodeLength(&(buf[point]),len-point,&offset);
	if(pdulength<0 || pdulength != len-point-offset) return false; //PDU����У��
	point += offset;
	if(point>=len) return false;
	//requsetID
	value = 0;
	if( !SNMPPdu::decodeInteger32(&(buf[point]),len-point,&value,&offset) )  
	{
		return false;
	}
	requestID = value;


	point += offset;
	if(point>=len) return false;
	//error status
	value = 0;
	if( !SNMPPdu::decodeInteger32(&(buf[point]),len-point,&value,&offset) )  
	{
		return false;
	}
	errorStatus = value;
	point += offset;
	if(point>=len) return false;
	//error index
	value = 0;
	if( !SNMPPdu::decodeInteger32(&(buf[point]),len-point,&value,&offset) )  
	{
		return false;
	}
	errorIndex = value;
	point += offset;
	if(point>=len) return false;
	//varialbindings
	if(buf[point]!=0x30) return false;
	point ++;
	if(point>=len) return false;
	pdulength = SNMPPdu::decodeLength(&(buf[point]),len-point,&offset);
	if(pdulength<0 || pdulength != len-point-offset) return false; //PDU����У��
	point += offset;
	if(point>=len) return false;
	//begin variablebinding decode
	uint32 vbnum = VariableBindings::getVBNumberFromBuf(&(buf[point]),len-point);

	if(vbnum==0 || vbnum == 0xffffffff) return false;
	if(variableBindings.variableBinding == NULL || vbnum>variableBindings.vbsmemsize)
	{
		variableBindings.variableBinding = NULL;
		variableBindings.vbsLength = 0;
		variableBindings.vbsmemsize = 0;
		variableBindings.newVBS(vbnum);
	}
	else
	{
		variableBindings.vbsLength = vbnum;
	}
	for(int i=0;i<vbnum;i++)
	{
		if(buf[point]!=0x30) return false; //0x30У��
		point ++;
		if(point>=len) return false;
		pdulength = SNMPPdu::decodeLength(&(buf[point]),len-point,&offset);
		if(pdulength<0 ) return false; //PDU����У��
		point += offset;
		if(point>=len) return false;
		uint8 syt = Variable::getBERSyntax(&(buf[point]),len-point);
		if(syt != VT_OID) return false;	//������OID
		
		variableBindings.variableBinding[i].oid.syntax = VT_OID;
		if( !variableBindings.variableBinding[i].oid.decode(&(buf[point]),len-point,&offset) )
			return false;
		point += offset;
		if(point>=len) return false;
		syt = Variable::getBERSyntax(&(buf[point]),len-point);
		if(syt == 0) return false;
		variableBindings.variableBinding[i].value.syntax = syt;
		if( !variableBindings.variableBinding[i].value.decode(&(buf[point]),len-point,&offset) )
			return false;
			
		
		point += offset;



	}
										  
	return true;													

}
int SNMPPdu::getPDUBerLength()
{

	int len = variableBindings.getBerLength();

	len = len+ 1+ getLengthBerLength(len);
	{ //errorIndex
		int tp = getInteger32BerLength(errorIndex);
		len += tp+1+getLengthBerLength(tp);
	}
	{ //errorStatus
		int tp = getInteger32BerLength(errorStatus);
		len += tp+1+getLengthBerLength(tp);
	}
	{ //requestID
		int tp = getInteger32BerLength(requestID);
		len += tp+1+getLengthBerLength(tp);
	}

	len = getLengthBerLength(len)+1 +len ;//command and len
	{ //Community
		int tp = cmtylen;
		len += tp+1+getLengthBerLength(tp);
	}
	{ //version
		int tp = getInteger32BerLength(version);
		len += tp+1+getLengthBerLength(tp);
	}

	return len;	
} 
int SNMPPdu::getPDUCmdBerLength()
{
	int len = variableBindings.getBerLength();
	len = len+ 1+ getLengthBerLength(len);
	{ //errorIndex
		int tp = getInteger32BerLength(errorIndex);
		len += tp+1+getLengthBerLength(tp);
	}
	{ //errorStatus
		int tp = getInteger32BerLength(errorStatus);
		len += tp+1+getLengthBerLength(tp);
	}
	{ //requestID
		int tp = getInteger32BerLength(requestID);
		len += tp+1+getLengthBerLength(tp);
	}
	return len;	
} 
bool SNMPPdu::encode(unsigned char *buf,int buflen,int pklen)
{
//	int pklen = getPDUBerLength();
//	int buflen =  pklen+1+ getLengthBerLength(pklen);
//	buf = new unsigned char[buflen];
//	*len = buflen;
	return encodeData(buf,buflen,pklen);
}

bool SNMPPdu::encodeData(unsigned char *buf,int len,int pklen)	//��PDU�л��buffer
{
	int point = 0;
	int offset;
	buf[0] = 0x30;
	offset = encodeLength(&(buf[1]),len-1,pklen);//�ܳ���
	point = offset+1;
	offset = encodeInteger32( &(buf[point]),len-point,version,VT_Integer32);//version
	point += offset;
	buf[point-1] = 0x01;
	offset = encodeOctetString( &(buf[point]),len-point,Community,cmtylen,VT_OctetString);
	point += offset;
	buf[point] =  commond;
	point += 1;
	offset = encodeLength(&(buf[point]),len-point,getPDUCmdBerLength());//����
	point += offset;
	offset = encodeInteger32( &(buf[point]),len-point,requestID,VT_Integer32);//requestID
	point += offset;
	offset = encodeInteger32( &(buf[point]),len-point,errorStatus,VT_Integer32);//errorStatus
	point += offset;
	offset = encodeInteger32( &(buf[point]),len-point,errorIndex,VT_Integer32);//errorIndex
	point += offset;
	variableBindings.encodeData(&(buf[point]),len-point);


	
	return true;
}
/*
	���������ֶ�,
	buf:   PDU�Ļ���buffer
	len:   buffer���ó���
	offset:	 ����ռ�õ��ֽ���
	����ֵ:	 ����ֵ,С��0��ʾ��Ч�ĳ����ֶ�
*/
int SNMPPdu::decodeLength(unsigned char *buf,int len,uint8 *offset)	//��buffer�л񳤶�
{
	if(buf ==NULL || len<=0) return -1;
	if(buf[0]<0x80)
	{
		*offset = 1;
		return buf[0];
	}
	else
	{
		uint8 llen = (uint8)(buf[0] & 0x7f);
		if(llen > 4 || llen == 0 ) return -1;
		if((llen+1)>len) return -1;//���Ȳ���
		if(llen == 1)
		{
			*offset = 2;
			return buf[1] & 0xff;
		}
		else if(llen == 2)
		{
			*offset = 3;
			return (((buf[1] & 0xff)<<8) | (buf[2] & 0xff));
		}
		else if(llen == 3)
		{
			*offset = 4;
			return (((buf[1] & 0xff)<<16) | ((buf[2] & 0xff)<<8) | (buf[3] & 0xff));
		}
		else if(llen == 4)
		{
			*offset = 5;
			return (((buf[1] & 0xff)<<24) | ((buf[2] & 0xff)<<16) | ((buf[3] & 0xff)<<8) | (buf[4] & 0xff));
		}
	}
	return -1;

}
/*
	���볤���ֶ�,
	buf:   �����������buffer
	len:   buffer���ó���		 
	length:	 ����ֵ
	����ֵ:	 ����ʹ�õ��ֽڳ���,С��0Ϊ����ʧ��
*/
int SNMPPdu::encodeLength(unsigned char *buf,int len,int length)	//�ӳ����л�buffer
{
	if(buf == NULL || len<=0) return -1;
	if( len < getLengthBerLength(length) ) return -1;
	if(length<0)
	{
		buf[0] = 0x84;
		buf[1] = (uint8)((length>>24) & 0xff);
		buf[2] = (uint8)((length>>16) & 0xff);
		buf[3] = (uint8)((length>>8) & 0xff);
		buf[4] = (uint8)((length) & 0xff);
		return 5;
	}
	else if(length<0x80)
	{
		buf[0] = (uint8)length;
		return 1;
	}
	else if(length<=0xff)
	{
		buf[0] = 0x81;
		buf[1] = (uint8)length;
		return 2;
	}
	else if(length<=0xffff)
	{
		buf[0] = 0x82;
		buf[1] = (uint8)((length>>8) & 0xff);
		buf[2] = (uint8)((length) & 0xff); 		
		return 3;
	}
	else if(length<=0xffffff)
	{
		buf[0] = 0x83;
		buf[1] = (uint8)((length>>16) & 0xff);
		buf[2] = (uint8)((length>>8) & 0xff);
		buf[3] = (uint8)((length) & 0xff);		
		return 4;
	}
	else if(length<=0xffffffff)
	{
		buf[0] = 0x84;
		buf[1] = (uint8)((length>>24) & 0xff);
		buf[2] = (uint8)((length>>16) & 0xff);
		buf[3] = (uint8)((length>>8) & 0xff);
		buf[4] = (uint8)((length) & 0xff);
		return 5;
	}
	else return -1;
}
int SNMPPdu::getLengthBerLength(int length)
{
	if(length<0)
	{
		return 5;
	}
	else if(length<0x80)
	{
		return 1;
	}
	else if(length<=0xff)
	{
		return 2;
	}
	else if(length<=0xffff)
	{
		return 3;
	}
	else if(length<=0xffffff)
	{
		return 4;
	}
	else if(length<=0xffffffff)
	{
		return 5;
	}
	else return 0;	
}
/*
	��buffer�������ȷ��octetstring
	buf:   ����buffer
	len:   buffer���ó���
	value��octetstringֵ
	valuelen��octetstring buffer���ó���
	offset��ռ�õ��ֽ���
	����ֵ:	 ��ȷ���ֵ��־
*/	
bool SNMPPdu::decodeOctetString(unsigned char *buf,int len,unsigned char *value,int *valuelen,uint8 *offset)
{
	
	if(buf == NULL || len<=1) return false;
	if(value == NULL || *valuelen<=0) return false;

	if(buf[0]!=VT_OctetString && buf[0]!=VT_IPAddress ) return false;

	uint8 os= 0;
	int length = SNMPPdu::decodeLength(&(buf[1]),len-1,&os);

	if(length<0 || *valuelen<length) return false;
	for(int i=0;i<length;i++)
	{
		value[i] = buf[i+os+1];
	}
	*valuelen = length;
	*offset = (uint8)(length+os+1);
	return true;

}
int SNMPPdu::encodeOctetString(unsigned char *buf,int len,unsigned char *value,int valuelen,uint8 type)
{
	int lgth = getLengthBerLength(valuelen);
	if(buf == NULL || len<(valuelen+lgth+1)) return 0;
	buf[0] = type;
	encodeLength(&(buf[1]),len-1,valuelen);
	for(int i=0;i<valuelen;i++)
	{
		buf[lgth+1+i] = value[i];
	}
	return (valuelen+lgth+1);
												
}


/*
	��buffer�������ȷ������
	buf:   ����buffer
	len:   buffer���ó���
	value������ֵ
	offset��ռ�õ��ֽ���
	����ֵ:	 ��ȷ���ֵ��־
*/	
bool SNMPPdu::decodeInteger32(unsigned char *buf,int len,uint32 *value,uint8 *offset)
{
	if(buf == NULL || len<=1) return false;
	if(buf[0]!=VT_Integer32) return false;  //�Ƿ���integer32����
	uint8 os= 0;
	int length = SNMPPdu::decodeLength(&(buf[1]),len-1,&os);   //integer32ֵ�ó���
	if(length<=0 || length>4 || os != 1) return false;		   //���Ȳ�Ӧ�ô���4�ֽ�
	if(len<length+2) return false;

	if((buf[2]& 0x80)>0)
	{			   
		*value = 0xffff;
	}
	else
	{
		*value = 0x00;
	}
	for(int i=0;i<length;i++)
	{
		 *value = ((*value)<<8) | buf[2+i];
	} 
	*offset = (uint8)(length+2);
	return true;

}
/*
	���������ֶ�,
	buf:   �����������buffer
	len:   buffer���ó���		 
	value:	 ����ֵ
	type:	���ͣ����������Ρ�count32��
	����ֵ:	 ����ʹ�õ��ֽڳ���,С��0Ϊ����ʧ��
*/
int SNMPPdu::encodeInteger32(unsigned char *buf,int len,uint32 value,uint8 type)
{
	int intsize = getInteger32BerLength(value);
	int lgth = getLengthBerLength(intsize);
	if(buf == NULL || len<(intsize+lgth+1)) return 0;
	buf[0] = type;
	encodeLength(&(buf[1]),len-1,intsize);

	uint32 integer = value;
	for(int i=0;i<intsize;i++)
	{
		buf[lgth+intsize-i] =  (uint8)((integer >> (i*8)) & 0xff);
	}
	return intsize+lgth+1;

}
int SNMPPdu::getInteger32BerLength(int value)
{
   	int integer = value;
    uint32 mask;
    int intsize = 4;

    /*
     * Truncate "unnecessary" bytes off of the most significant end of this
     * 2's complement integer.  There should be no sequence of 9
     * consecutive 1's or 0's at the most significant end of the
     * integer.
     */
    mask = 0xFF800000;
    /* mask is 0xFF800000 on a big-endian machine */
    while((((integer & mask) == 0) || ((integer & mask) == mask))
          && intsize > 1){
      intsize--;
      integer <<= 8;
    }
	return intsize;
}
bool SNMPPdu::decodeUnsignedInteger32(unsigned char *buf,int len,uint32 *value,uint8 *offset)
{
	if(buf == NULL || len<=1) return false;
	if(buf[0]==VT_Integer32 || buf[0]==VT_Counter32
		|| buf[0]==VT_Gauge32|| buf[0]==VT_TimeTicks
		|| buf[0]==0x47)
	{
	}
	else
	{
	 	return false;  //�Ƿ���integer32����
	}
	uint8 os= 0;
	int length = SNMPPdu::decodeLength(&(buf[1]),len-1,&os);   //integer32ֵ�ó���
	if(length<=0 || length>5 || os != 1) return false;		   //���Ȳ�Ӧ�ô���5�ֽ�
	if(len<length+2) return false;

    *value = 0;
 
	
    // check for legal uint size
    if ((length > 5) || ((length > 4) && (buf[1+os] != 0x00))) {
      	return false;
    }													   

	int i=0;
	if(buf[2] == 0x00) i=1;
	for(;i<length;i++)
	{
		*value = (*value << 8) | (buf[i+2] & 0xFF);	
	}
	*offset= (uint8)(length + 2);
    return true;
			
}
int SNMPPdu::encodeUnsignedInteger32(unsigned char *buf,int len,uint32 value,uint8 type)
{
	int intsize = getUnsignedInteger32BerLength(value);
	int lgth = getLengthBerLength(intsize);
	if(buf == NULL || len<(intsize+lgth+1)) return 0;
	buf[0] = type;
	encodeLength(&(buf[1]),len-1,intsize);


    // special case, add a null byte for len of 5
    if (intsize == 5) {
		buf[1+lgth] = 0x00;
      	for (int x=1; x<intsize; x++) 
		{
	  		buf[1+lgth+x] = (uint8)((value >> (8 * (4 - x) ))& 0xff);
      	}
    }
    else
    {
      	for (int x=0; x<intsize; x++) {
	  		buf[1+lgth+x] =  (uint8)((value >> (8 * ((intsize - 1) - x) ))& 0xff);
     	}
    }
	return intsize+lgth+1;
}
int SNMPPdu::getUnsignedInteger32BerLength(uint32 value)
{
    int len = 1;
    if ((( value >> 24) & 0xff) != 0) {
      len = 4;
    }
    else if ((( value >> 16) & 0xff) !=0) {
      len = 3;
    }
    else if ((( value >> 8) & 0xff) !=0) {
      len = 2;
    }
    // check for 5 byte len where first byte will be
    // a null
    if ((( value >> (8 * (len -1))) & 0x080) !=0)	{
      len++;
    }
	return len;
}
bool SNMPPdu::decodeInteger64(unsigned char *buf,int len,uint32 *high,uint32 *low,uint8 *offset)
{
	if(buf == NULL || len<=1) return false;
	if(buf[0]==VT_Integer32 || buf[0]==VT_Counter64	)
	{
	}
	else
	{
	 	return false;  //�Ƿ���integer32����
	}
	uint8 os= 0;
	int length = SNMPPdu::decodeLength(&(buf[1]),len-1,&os);   //integer32ֵ�ó���
	if(length<=0 || length>9 || os != 1) return false;		   //���Ȳ�Ӧ�ô���5�ֽ�
	if(len<length+2) return false;

	
    // check for legal uint size
    if ((length > 9) || ((length > 8) && (buf[1+os] != 0x00))) {
      	return false;
    }													   
    *high = 0;
    *low = 0;
	if(length == 1)
	{
		*low = buf[1+os] & 0xff;
	}
	else if(length == 2)
	{
		*low = (buf[1+os+1] & 0xff) | ( (buf[1+os] & 0xff)<<8);
	}
	else if(length == 3)
	{
		*low = (buf[1+os+2] & 0xff) | ( (buf[1+os+1] & 0xff)<<8)|( (buf[1+os] & 0xff)<<16);
	}
	else if(length == 4)
	{
		*low = (buf[1+os+3] & 0xff) | ( (buf[1+os+2] & 0xff)<<8)|( (buf[1+os+1] & 0xff)<<16)|( (buf[1+os] & 0xff)<<24);
	}
	else if(length == 5)
	{
		*high = buf[1+os] & 0xff;
		*low = (buf[1+os+4] & 0xff) | ( (buf[1+os+3] & 0xff)<<8)|( (buf[1+os+2] & 0xff)<<16)|( (buf[1+os+1] & 0xff)<<24);
	}
	else if(length == 6)
	{
		*high = buf[1+os+1] & 0xff | ( (buf[1+os] & 0xff)<<8);
		*low = (buf[1+os+5] & 0xff) | ( (buf[1+os+4] & 0xff)<<8)|( (buf[1+os+3] & 0xff)<<16)|( (buf[1+os+2] & 0xff)<<24);
	}
	else if(length == 7)
	{
		*high = buf[1+os+2] & 0xff | ( (buf[1+os+1] & 0xff)<<8)| ( (buf[1+os] & 0xff)<<16);
		*low = (buf[1+os+6] & 0xff) | ( (buf[1+os+5] & 0xff)<<8)|( (buf[1+os+4] & 0xff)<<16)|( (buf[1+os+3] & 0xff)<<24);
	}
	else if(length == 8)
	{
		*high = buf[1+os+3] & 0xff | ( (buf[1+os+2] & 0xff)<<8) | ( (buf[1+os+1] & 0xff)<<16) | ( (buf[1+os] & 0xff)<<24);
		*low = (buf[1+os+7] & 0xff) | ( (buf[1+os+6] & 0xff)<<8)|( (buf[1+os+5] & 0xff)<<16)|( (buf[1+os+4] & 0xff)<<24);
	}
	else if(length == 9)
	{
		*high = buf[1+os+4] & 0xff | ( (buf[1+os+3] & 0xff)<<8) | ( (buf[1+os+2] & 0xff)<<16) | ( (buf[1+os+1] & 0xff)<<24);
		*low = (buf[1+os+8] & 0xff) | ( (buf[1+os+7] & 0xff)<<8)|( (buf[1+os+6] & 0xff)<<16)|( (buf[1+os+5] & 0xff)<<24);
	}

	*offset= (uint8)(length + 2);
    return true;
}
int SNMPPdu::encodeInteger64(unsigned char *buf,int len,uint32 high,uint32 low,uint8 type)
{
 	int intsize = getInteger64BerLength(high,low);
	int lgth = getLengthBerLength(intsize);
	if(buf == NULL || len<(intsize+lgth+1)) return 0;
	buf[0] = type;
	encodeLength(&(buf[1]),len-1,intsize);

// special case, add a null byte for len of 5
    if (intsize == 9) {
		buf[1+lgth] = 0x00;
		buf[1+lgth+1] = (uint8)((high >> 24) & 0xff);
		buf[1+lgth+2] = (uint8)((high >> 16) & 0xff);
		buf[1+lgth+3] = (uint8)((high >> 8) & 0xff);
		buf[1+lgth+4] = (uint8)((high ) & 0xff);
		buf[1+lgth+5] = (uint8)((low >> 24) & 0xff);
		buf[1+lgth+6] = (uint8)((low >> 16) & 0xff);
		buf[1+lgth+7] = (uint8)((low >> 8) & 0xff);
		buf[1+lgth+8] = (uint8)((low ) & 0xff);

	}
	else if(intsize == 1)
	{
		buf[1+lgth] = (uint8)((low ) & 0xff);	
	}
	else if(intsize == 2)
	{
		buf[1+lgth] = (uint8)((low >>8) & 0xff);	
		buf[1+lgth+1] = (uint8)((low ) & 0xff);	
	}
	else if(intsize == 3)
	{
		buf[1+lgth] = (uint8)((low >>16) & 0xff);	
		buf[1+lgth+1] = (uint8)((low >>8) & 0xff);	
		buf[1+lgth+2] = (uint8)((low ) & 0xff);	
	}
	else if(intsize == 4)
	{
		buf[1+lgth] = (uint8)((low >>24) & 0xff);	
		buf[1+lgth+1] = (uint8)((low >>16) & 0xff);	
		buf[1+lgth+2] = (uint8)((low >>8) & 0xff);	
		buf[1+lgth+3] = (uint8)((low ) & 0xff);	
	}
	else if(intsize == 5)
	{
		buf[1+lgth] = (uint8)((high ) & 0xff);	
		buf[1+lgth+1] = (uint8)((low >>24) & 0xff);	
		buf[1+lgth+2] = (uint8)((low >>16) & 0xff);	
		buf[1+lgth+3] = (uint8)((low >>8) & 0xff);	
		buf[1+lgth+4] = (uint8)((low ) & 0xff);	
	}
	else if(intsize == 6)
	{
		buf[1+lgth] = (uint8)((high >>8) & 0xff);	
		buf[1+lgth+1] = (uint8)((high ) & 0xff);	
		buf[1+lgth+2] = (uint8)((low >>24) & 0xff);	
		buf[1+lgth+3] = (uint8)((low >>16) & 0xff);	
		buf[1+lgth+4] = (uint8)((low >>8) & 0xff);	
		buf[1+lgth+5] = (uint8)((low ) & 0xff);	
	}
	else if(intsize == 7)
	{
		buf[1+lgth] = (uint8)((high >>16) & 0xff);	
		buf[1+lgth+1] = (uint8)((high >>8) & 0xff);	
		buf[1+lgth+2] = (uint8)((high ) & 0xff);	
		buf[1+lgth+3] = (uint8)((low >>24) & 0xff);	
		buf[1+lgth+4] = (uint8)((low >>16) & 0xff);	
		buf[1+lgth+5] = (uint8)((low >>8) & 0xff);	
		buf[1+lgth+6] = (uint8)((low ) & 0xff);	
	}
	else if(intsize == 8)
	{
		buf[1+lgth] = (uint8)((high >>24) & 0xff);	
		buf[1+lgth+1] = (uint8)((high >>16) & 0xff);	
		buf[1+lgth+2] = (uint8)((high >>8) & 0xff);	
		buf[1+lgth+3] = (uint8)((high ) & 0xff);	
		buf[1+lgth+4] = (uint8)((low >>24) & 0xff);	
		buf[1+lgth+5] = (uint8)((low >>16) & 0xff);	
		buf[1+lgth+6] = (uint8)((low >>8) & 0xff);	
		buf[1+lgth+7] = (uint8)((low ) & 0xff);	
	}
	return intsize+lgth+1;


}
int SNMPPdu::getInteger64BerLength(uint32 high,uint32 low)
{
	if( (high & 0x80000000 ) != 0) return 9;
	if( high == 0 && (low < 0x80) ) return 1;
	if( high == 0 && (low < 0x8000) ) return 2;
	if( high == 0 && (low < 0x800000) ) return 3;
	if( high == 0 && (low < 0x80000000) ) return 4;
	if( high == 0 && (low >= 0x80000000) ) return 5;
	if( high < 0x80) return 5;
	if( high < 0x8000) return 6;
	if( high < 0x800000) return 7;
	if( high < 0x80000000) return 8;
	return 8;
}
/*
	��buffer�������ȷ��OID
	buf:   ����buffer
	len:   buffer���ó���
	value����������ָ��
	valuelen���ó���
	value������
	offset��ռ�õ��ֽ���
	����ֵ:	 ��ȷ���ֵ��־
*/	
uint32 SNMPPdu::decodeOID(unsigned char *buf,int len,int *valuelen,uint8 *offset,uint32 *oidbuf,uint32 maxlen)
{
	if(buf == NULL || len<=1 || oidbuf== NULL) return FAILED;
	if(buf[0] != VT_OID) return FAILED;

	int length = SNMPPdu::decodeLength(&(buf[1]),len-1,offset);	  //�����ݰ�Ȳ�У��
	if(length<0 && len< (length+*offset+1) ) return FAILED;
	
	if((length+2) >= maxlen) return FAILED;
	
	if(length == 0)
	{
		oidbuf[0] = oidbuf[1] = 0;
	}

	int subidentifier;
	int pos = 1;
	int tmppoint = *offset+1;
	int lth = length;


    while (lth > 0){
      subidentifier = 0;
      int b;
      do {	/* shift and add in low order 7 bits */
        int next = buf[tmppoint];
		tmppoint++;
        
        b = next & 0xFF;
        subidentifier = (subidentifier << 7) + (b & 0x7f);
        lth--;
      } while ((lth > 0) && ((b & 0x80) != 0));	/* last byte has high bit clear */
      oidbuf[pos] = subidentifier;
	  pos++;
    }

    /*
    * The first two subidentifiers are encoded into the first component
    * with the value (X * 40) + Y, where:
    *	X is the value of the first subidentifier.
    *  Y is the value of the second subidentifier.
    */
    subidentifier = oidbuf[1];
    if (subidentifier == 0x2B){
      oidbuf[0] = 1;
      oidbuf[1] = 3;
    }
    else {
      oidbuf[1] = (subidentifier % 40);
      oidbuf[0] = ((subidentifier - oidbuf[1]) / 40);
    }
    if (pos < 2) {
      pos = 2;
    }
	
	*valuelen = pos;
	*offset	= (uint8)(*offset + length+1);
	return SUCCESS;
	
}
int SNMPPdu::encodeOID(unsigned char *buf,int len,uint32 *value,int valuelen)
{
	int size = getOIDBerLength(value,valuelen);
	int lgth = getLengthBerLength(size);
	if(buf == NULL || len<(size+lgth+1)) return 0;
	buf[0] = VT_OID;		
	encodeLength(&(buf[1]),len-1,size);

	int encodedLength = valuelen;
    int rpos = 0;

    if (valuelen < 2 || value == NULL){
		buf[lgth+1] = 0x00;
      	encodedLength = 0;
    }
    else 
	{
      buf[lgth+1] = (uint8)((value[1] + (value[0] * 40)) & 0xFF);
      encodedLength -= 2;
      rpos = 2;
    }
	int i=0;
    while (encodedLength-- > 0){
      uint32 subid = (value[rpos++] & 0xFFFFFFFF);
      if (subid < 127) {
	  	buf[lgth+2+i] = (uint8)(subid & 0xFF);
		i++;
      }
      else {
        uint32 mask = 0x7F; /* handle subid == 0 case */
        uint32 bits = 0;

        /* testmask *MUST* !!!! be of an unsigned type */
        for (uint32 testmask = 0x7F, testbits = 0; testmask != 0;
             testmask <<= 7, testbits += 7) {
          if ((subid & testmask) > 0) {	/* if any bits set */
            mask = testmask;
            bits = testbits;
          }
        }
        /* mask can't be zero here */
        for (; mask != 0x7F; mask >>= 7, bits -= 7){
          /* fix a mask that got truncated above */
          if (mask == 0x1E00000) {
            mask = 0xFE00000;
          }
		  buf[lgth+2+i] = (uint8)(((subid & mask) >> bits) | 0x80);
		  i++;
        }
		buf[lgth+2+i] = (uint8)(subid & mask);
		i++;
      }
    }
	return 	size+lgth+1;
}
int SNMPPdu::getOIDBerLength(uint32 *value,int valuelen)
{
	if(value == NULL) return 1;
	int length = 1; // for first 2 subids
    for (int i = 2; i < valuelen; i++) {
      uint32 v = value[i] & 0xFFFFFFFF;
      if (v < 0x80) { //  7 bits long subid
        length += 1;
      }
      else if (v < 0x4000) {  // 14 bits long subid
        length += 2;
      }
      else if (v < 0x200000) { // 21 bits long subid
        length += 3;
      }
      else if (v < 0x10000000) { // 28 bits long subid
        length += 4;
      }
      else {                     // 32 bits long subid
        length += 5;
      }
    }
    return length;
}

#endif
