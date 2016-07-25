#ifndef VariableBindings_H
#define VariableBindings_H

#include "VariableBinding.h"
class VariableBindings
{
public:
	VariableBinding *variableBinding;
	uint8 vbsLength;						//变量绑定列表长度
	uint8 vbsmemsize;

public:
	VariableBindings(void);
	virtual ~VariableBindings(void);
	static uint32 getVBNumberFromBuf(unsigned char *buf,uint32 len);
	
	void newVBS(int len);
	VariableBinding* getAt(int index);
	uint8 getVBSLength();

	int getBerLength();
	uint8 encodeData(unsigned char *buf,int len);	//从PDU中获得buffer
};
#endif
