/*
 * BaseChip.h
 *
 *  Created on: 2013-11-26
 *      Author: Administrator
 */

#ifndef BASECHIP_H_
#define BASECHIP_H_

#include <string>
#include "EZ_types.h"


typedef enum {
    succeed,
    failed,
    donothing

}Chip_INIT_RESULT;

class BaseChip {
public:
    BaseChip(const std::string& n);
    virtual ~BaseChip();

    std::string& itsName(void) {
        return name;
    };

    virtual Chip_INIT_RESULT ChipInit(void) = 0;

	virtual std::string GetVerInfo(void){
		return "";
	};
private:
    std::string name;
	virtual std::string GetChipVerInfo( const std::string ,const uint16){
		return 0;
	}
};

#endif /* BASECHIP_H_ */
