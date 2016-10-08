/*
 * CmdRing.h
 *
 *  Created on: 2016年9月20日
 *      Author: Administrator
 */

#ifndef SOURCE_HIS_APP_COMPONENTELEMENT_COMPMISC_FANPOWCOMMAND_CMDRING_H_
#define SOURCE_HIS_APP_COMPONENTELEMENT_COMPMISC_FANPOWCOMMAND_CMDRING_H_

#include "VFCommand.h"
class CmdRing: public VFCommand {
public:
    CmdRing(uint8 ring);
    virtual ~CmdRing();

    virtual uint8 getNMByte(void) {
        return cmd;
    };
    virtual uint8 getParaLen(void){
        return 1;
    }
    virtual uint8* getPara(void){
        return para;
    }

private:
    uint8 cmd;
    uint8 para[1]; //1 ring; 0 stop
};

#endif /* SOURCE_HIS_APP_COMPONENTELEMENT_COMPMISC_FANPOWCOMMAND_CMDRING_H_ */
