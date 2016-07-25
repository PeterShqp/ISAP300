/*
 * BAlarmDisplay.h
 *
 *  Created on: 2014
 *      Author: Administrator
 */

#ifndef BALARMDISPLAY_H_
#define BALARMDISPLAY_H_

#include <list>
#include <string>

class AlarmInstance;
class BAlarmDisplay {
    BAlarmDisplay();
public:
    BAlarmDisplay(const char* name);
    virtual ~BAlarmDisplay();

    virtual std::string& getName(void) {
        return name;
    };

    virtual void update(AlarmInstance*) = 0;
    virtual void display(bool alarm) = 0;

    void addInstance(AlarmInstance*);
    void delInstance(AlarmInstance*);
protected:
    std::list<AlarmInstance*> Obs; //告警输出所观察的告警对象
private:
    std::string name;
};

#endif /* BALARMDISPLAY_H_ */
