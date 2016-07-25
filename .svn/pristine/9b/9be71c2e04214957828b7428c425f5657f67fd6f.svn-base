/*
 * SrcAlarmVCG.h
 *
 *  Created on: 2014Äê10ÔÂ28ÈÕ
 *      Author: Administrator
 */

#ifndef SRCALARMVCG_H_
#define SRCALARMVCG_H_

#include "BAlarmSource.h"
#include "EOSCardAlarmDataDefine.h"

class VCG;

class SrcAlarmVCG: public BAlarmSource {
public:
    SrcAlarmVCG(BAlarmModule*, VCG*, SrcVCGAlarm_Data*);
    virtual ~SrcAlarmVCG();

    virtual void makeAlarmSignal(void);
    virtual bool ifSrcRestrain();
    virtual bool getAlarm(int type);
    virtual std::string getTypeName(int type);
    virtual uint32 itsID(void);
    virtual std::string& itsName(void);
private:
    VCG* vcg;
    SrcVCGAlarm_Data* PConfigData;
};

#endif /* SRCALARMVCG_H_ */
