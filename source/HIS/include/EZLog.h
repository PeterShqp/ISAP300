/*
 * EZLog.h
 *
 *  Created on: 2016年9月5日
 *      Author: Administrator
 */

#ifndef SOURCE_HIS_TOOLS_EZLOG_H_
#define SOURCE_HIS_TOOLS_EZLOG_H_

#include <string>
#include "EZ_types.h"

class EZLog {
    EZLog() {};
    EZLog(EZLog&) {};
    virtual ~EZLog() {};
    static EZLog log;
public:
    static EZLog& instance(void) {
        return log;
    };
    void init(void);
    void record(std::string& txt);
    void record(const char* s);

private:
    uint32 MAX_SIZE;
    const char* curFile;
    bool ifFileFull(const char* f);
    bool ifFileExist(const char* f);
    void findActiveFile(void);
    void switchCurrFile(void);
};

#endif /* SOURCE_HIS_TOOLS_EZLOG_H_ */
