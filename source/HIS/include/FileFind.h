/*
 * FileFind.h
 *
 *  Created on: 2016年6月16日
 *      Author: Administrator
 */

#ifndef SOURCE_HIS_TOOLS_FILEFIND_H_
#define SOURCE_HIS_TOOLS_FILEFIND_H_

#include "os.h"

class FileFind {
public:
    FileFind();
    virtual ~FileFind();

    static bool getCfgFileInfoByID(uint16 id, FINFO& info);
    static bool getBitFileInfoByID(uint16 id, FINFO& info);
};

#endif /* SOURCE_HIS_TOOLS_FILEFIND_H_ */
