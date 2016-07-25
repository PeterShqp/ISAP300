/*
 * EthMemory.cpp
 *
 *  Created on: 2013-7-18
 *      Author: Administrator
 */

#include "EthMemory.h"
#include "os.h"
#include "sysapi.h"

_declare_box(datapool,1024,64); //��̬����ڴ�� ÿ��1024bytes,��64��
_declare_box(framepool,8,64); //��̬֡ͷ�ڴ�أ�ÿ��8bytes,��64��

void InitEthMemory(void) {
	_init_box(datapool, sizeof(datapool), 1024);//��ʼ������ڴ�أ�����ÿ����1024�ֽڹ̶���С
	_init_box(framepool, sizeof(framepool), 8);//��ʼ��֡ͷ�ڴ�أ�����ÿ����8�ֽ�
}

/*
 * �̰߳�ȫ�Ķ�̬�ڴ���亯��
 */
LAYER2FRAME* alloc_Eth_mem(uint16 len) {
    LAYER2FRAME* f = 0;
    int_disable_eth_real();
	f = _calloc_box(framepool);//��Ϊ֡�ṹ�����ڴ�
	if( f ) {
		f->length = len;
		f->frame = _calloc_box(datapool);//Ϊ֡����ݷ����ڴ�
		if( f->frame == 0 ) {
			_free_box(framepool, f);//���֡��ݷ���ʧ�����ͷ�֡�ṹ�ڴ�
			int_enable_eth_real();
			return 0;
		}
	}
	int_enable_eth_real();
	return f;
}
void free_Eth_mem(LAYER2FRAME* f) {
	if( f ) {
		_free_box(datapool, f->frame);
		_free_box(framepool, f);
	}
}

LAYER2FRAME* alloc_Eth_mem_interrupt(uint16 len) {
     LAYER2FRAME* f = 0;//��Ϊ֡�ṹ�����ڴ�
     f = _calloc_box(framepool);
     if( f ) {
         f->length = len;
         f->frame = _calloc_box(datapool);//Ϊ֡����ݷ����ڴ�
         if( f->frame == 0 ) {
             _free_box(framepool, f);//���֡��ݷ���ʧ�����ͷ�֡�ṹ�ڴ�
             return 0;
         }
     }
     return f;
}

void free_Eth_mem_interrupt(LAYER2FRAME* f) {
    if( f ) {
        _free_box(datapool, f->frame);
        _free_box(framepool, f);
    }
}
