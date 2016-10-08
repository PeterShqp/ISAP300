/*
 * CmdFanCtrl.h
 *
 *  Created on: 2016年9月29日
 *      Author: Administrator
 */

#ifndef SOURCE_HIS_APP_COMPONENTELEMENT_COMPMISC_FANPOWCOMMAND_CMDFANCTRL_H_
#define SOURCE_HIS_APP_COMPONENTELEMENT_COMPMISC_FANPOWCOMMAND_CMDFANCTRL_H_

#include "VFCommand.h"
class CmdFanCtrl: public VFCommand {
public:
    CmdFanCtrl(uint8 sn, uint8 en);
    virtual ~CmdFanCtrl();

    virtual uint8 getNMByte(void) {
        return cmd;
    };
    virtual uint8 getParaLen(void){
        return 2;
    }
    virtual uint8* getPara(void){
        return para;
    }

private:
    uint8 cmd;
    uint8 para[2]; //1 ring; 0 stop
};

#endif /* SOURCE_HIS_APP_COMPONENTELEMENT_COMPMISC_FANPOWCOMMAND_CMDFANCTRL_H_ */
