/*
 * EOS4NCardAlarmModule.h
 *
 *  Created on: 2015年5月18日
 *      Author: Administrator
 */

#ifndef EOS4NCARDALARMMODULE_H_
#define EOS4NCARDALARMMODULE_H_

#include "BAlarmModule.h"

class Card4EOSN;
class EOS4NCardAlarmModule: public BAlarmModule {
public:
    EOS4NCardAlarmModule(Card4EOSN* c);
    virtual ~EOS4NCardAlarmModule();

    virtual void creatAlarmSource();
private:
    Card4EOSN* card;
};

#endif /* EOS4NCARDALARMMODULE_H_ */
