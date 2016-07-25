/*
 * ClockZarlink30122.cpp
 *
 *  Created on: 2014��11��19��
 *      Author: Administrator
 */

#include "ClockZarlink30122.h"
#include "ChipPCMLogic.h"


ClockZarlink30122::ClockZarlink30122(ChipPCMLogic* c) {
    chip = c;
}

ClockZarlink30122::~ClockZarlink30122() {

}

void ClockZarlink30122::initChip(void) {
    if( chip ) {
        chip->writeMSPI(0x01, 0x02); //��оƬ��λ���ⲿ�ܽ���Ч
        chip->writeMSPI(0x61, 0x23); //����Ĳ��ʱ��Ϊ77.76
    }

}


void ClockZarlink30122::selectFref(Fref_Channel_E ch) {
    if( ch == FrefChannel1 ) {
        if( chip ) {
            chip->writeMSPI(0x20, 0);
        }
    }
    else {
        if( chip ) {
            chip->writeMSPI(0x20, 1);
        }
    }
}
