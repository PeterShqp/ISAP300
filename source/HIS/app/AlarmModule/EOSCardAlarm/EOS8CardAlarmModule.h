/*
 * EOS8CardAlarmModule.h
 *
 *  Created on: 2014Äê10ÔÂ28ÈÕ
 *      Author: Administrator
 */

#ifndef EOS8CARDALARMMODULE_H_
#define EOS8CARDALARMMODULE_H_

#include "BAlarmModule.h"

class Card8EOS;
class EOS8CardAlarmModule: public BAlarmModule {
public:
    EOS8CardAlarmModule(Card8EOS* c);
    virtual ~EOS8CardAlarmModule();

    virtual void creatAlarmSource();
private:
    Card8EOS* card;
};

#endif /* EOS8CARDALARMMODULE_H_ */
