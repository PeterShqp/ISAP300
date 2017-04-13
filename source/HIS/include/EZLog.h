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
#include <vector>
#include "os.h"

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

    bool bufFull(void) {
    	if( bp >= MAX_BUF_SIZE ) {
    		return true;
    	}
    	return false;
    };
    void saveToFile(void);

    OS_TID task_save;
private:
    uint32 MAX_SIZE;
    const char* curFile;
    bool ifFileFull(const char* f);
    bool ifFileExist(const char* f);
    void findActiveFile(void);
    void switchCurrFile(void);
    std::vector<std::string> BufOfLog;
    int bp;
    const static int MAX_BUF_SIZE = 10;
};

#endif /* SOURCE_HIS_TOOLS_EZLOG_H_ */
