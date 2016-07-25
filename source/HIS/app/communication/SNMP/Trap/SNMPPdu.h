#ifndef SNMPPdu_H
#define SNMPPdu_H
#include "VariableBindings.h"

#define CommunityMaxLen 16
class VariableBinding;
class SNMPPdu
{
//static variable
public:
	//版本
	const static uint32 version1 = 0;
	const static uint32 version2c = 1;
	//数据包类型
	const static uint8 GET = 0xa0;
	const static uint8 SET = 0xa3;
	const static uint8 RESPONSE = 0xa2;
	const static uint8 GETNEXT = 0xa1;
	const static uint8 TRAP = 0xa7;
	//差错状态
	const static uint8 SNMP_ERROR_SUCCESS                 = 0;
	const static uint8 SNMP_ERROR_TOO_BIG                 = 1;
    const static uint8 SNMP_ERROR_NO_SUCH_NAME            = 2;//no use
    const static uint8 SNMP_ERROR_BAD_VALUE               = 3;//no use
    const static uint8 SNMP_ERROR_READ_ONLY               = 4;//no use
    const static uint8 SNMP_ERROR_GENERAL_ERROR           = 5;
    const static uint8 SNMP_ERROR_NO_ACCESS               = 6;
    const static uint8 SNMP_ERROR_WRONG_TYPE              = 7;
    const static uint8 SNMP_ERROR_WRONG_LENGTH            = 8;
    const static uint8 SNMP_ERROR_WRONG_ENCODING          = 9;
    const static uint8 SNMP_ERROR_WRONG_VALUE             =10;
    const static uint8 SNMP_ERROR_NO_CREATION             =11;
    const static uint8 SNMP_ERROR_INCONSISTENT_VALUE      =12;
    const static uint8 SNMP_ERROR_RESOURCE_UNAVAILABLE    =13;
    const static uint8 SNMP_ERROR_COMMIT_FAILED           =14;
    const static uint8 SNMP_ERROR_UNDO_FAILED             =15;
    const static uint8 SNMP_ERROR_AUTHORIZATION_ERROR     =16;
    const static uint8 SNMP_ERROR_NOT_WRITEABLE           =17;
    const static uint8 SNMP_ERROR_INCONSISTENT_NAME       =18;
public:
	uint32 version;						   	//版本，只支持V2c，v1的数据包以V2c格式返回
	uint8 Community[CommunityMaxLen];//共同体名称
	int cmtylen;
	uint8 commond;							//数据包类型
	uint32 requestID;						//请求ID
	uint32 errorStatus;						//差错状态
	uint32 errorIndex;						//差错索引
	
	VariableBindings	variableBindings;	//变量绑定列表

	bool isValid;

public:
	SNMPPdu(void);
	SNMPPdu(unsigned char *buf,int len,VariableBinding* vbs,int vbsmemlen);
	virtual ~SNMPPdu(void);
	bool encode(unsigned char *buf,int buflen,int pklen);

	static int decodeLength(unsigned char *buf,int len,uint8 *offset);	//从buffer中获长度
	static int encodeLength(unsigned char *buf,int len,int length);	//从长度中获buffer
	static int getLengthBerLength(int length);

	static bool decodeOctetString(unsigned char *buf,int len,unsigned char *value,int *valuelen,uint8 *offset);//string
	static int encodeOctetString(unsigned char *buf,int len,unsigned char *value,int valuelen,uint8 type);

	static bool decodeInteger32(unsigned char *buf,int len,uint32 *value,uint8 *offset);
	static int encodeInteger32(unsigned char *buf,int len,uint32 value,uint8 type);
	static int getInteger32BerLength(int value);

	static bool decodeUnsignedInteger32(unsigned char *buf,int len,uint32 *value,uint8 *offset);
	static int encodeUnsignedInteger32(unsigned char *buf,int len,uint32 value,uint8 type);
	static int getUnsignedInteger32BerLength(uint32 value);

	static bool decodeInteger64(unsigned char *buf,int len,uint32 *high,uint32 *low,uint8 *offset);
	static int encodeInteger64(unsigned char *buf,int len,uint32 high,uint32 low,uint8 type);
	static int getInteger64BerLength(uint32 high,uint32 low);

	static uint32 decodeOID(unsigned char *buf,int len,int *valuelen,uint8 *offset,uint32 *oidbuf,uint32 maxlen);
	static int encodeOID(unsigned char *buf,int len,uint32 *value,int valuelen);
	static int getOIDBerLength(uint32 *value,int valuelen);

	int getPDUBerLength();
private:
	bool decodeData(unsigned char *buf,int len);	//从buffer中获得PDU
	bool encodeData(unsigned char *buf,int len,int pklen);	//从PDU中获得buffer
	int getPDUCmdBerLength();

};
#endif
