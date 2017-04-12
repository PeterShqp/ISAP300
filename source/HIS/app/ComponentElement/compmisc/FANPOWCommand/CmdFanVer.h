/*
 * CmdFanVer.h
 *
 *  Created on: 2017年4月5日
 *      Author: Administrator
 */

#ifndef SOURCE_HIS_APP_COMPONENTELEMENT_COMPMISC_FANPOWCOMMAND_CMDFANVER_H_
#define SOURCE_HIS_APP_COMPONENTELEMENT_COMPMISC_FANPOWCOMMAND_CMDFANVER_H_

#include "VFCommand.h"

class CmdFanVer: public VFCommand {
public:
    CmdFanVer();
    virtual ~CmdFanVer();

    virtual uint8 getNMByte(void) {
        return cmd;
    };
    virtual uint8 getParaLen(void){
        return 0;
    }
    virtual uint8* getPara(void){
        return 0;
    }

private:
    uint8 cmd;
};

#endif /* SOURCE_HIS_APP_COMPONENTELEMENT_COMPMISC_FANPOWCOMMAND_CMDFANVER_H_ */
