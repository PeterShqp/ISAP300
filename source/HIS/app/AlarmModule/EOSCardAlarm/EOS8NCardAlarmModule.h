/*
 * EOS8NCardAlarmModule.h
 *
 *  Created on: 2015年5月18日
 *      Author: Administrator
 */

#ifndef EOS8NCARDALARMMODULE_H_
#define EOS8NCARDALARMMODULE_H_

#include "BAlarmModule.h"

class Card8EOSN;
class EOS8NCardAlarmModule: public BAlarmModule {
public:
    EOS8NCardAlarmModule(Card8EOSN* c);
    virtual ~EOS8NCardAlarmModule();

    virtual void creatAlarmSource();
private:
    Card8EOSN* card;
};

#endif /* EOS8NCARDALARMMODULE_H_ */
