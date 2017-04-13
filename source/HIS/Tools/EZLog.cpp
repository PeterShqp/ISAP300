/*
 * EZLog.cpp
 *
 *  Created on: 2016年9月5日
 *      Author: Administrator
 */

#include "EZLog.h"
#include <stdio.h>
#include "os.h"
#include "CPPTools.h"
#include <string.h>
EZLog EZLog::log;
OS_MUT mut_log;
const static char logAname[] = "A.log";
const static char logBname[] = "B.log";

TASK void saveLog();

void EZLog::record(std::string& txt) {

    os_mut_wait(mut_log, 0xffff);
    BufOfLog[bp++] = txt;
    os_mut_release(mut_log);
    os_evt_set(0x0001, task_save);
}

void EZLog::record(const char* s) {
	std::string txt(s);
	record(txt);
}

void EZLog::init(void) {
    os_mut_init(mut_log);
    MAX_SIZE = 6000;
    bp = 0;
    findActiveFile();
    task_save = os_tsk_create(saveLog, P_SAVE+1);
}

void EZLog::findActiveFile(void) {
	bool aexist = ifFileExist(logAname);
	bool bexist = ifFileExist(logBname);
	if( aexist && !bexist ) {
		curFile = logAname;
	}
	else if( !aexist && bexist ) {
		curFile = logBname;
	}
	else if( !aexist && !bexist ) {
		curFile = logAname;
	}
	else {
		if( !ifFileFull(logAname) ) {
			curFile = logAname;
		}
		else if( !ifFileFull(logBname) ) {
			curFile = logBname;
		}
		else {
			curFile = logAname;
		}
	}
}

void EZLog::switchCurrFile(void) {
	if( strcmp(curFile, logAname) == 0 ) {
		curFile = logBname;
	}
	else {
		curFile = logAname;
	}
	if( ifFileFull(curFile) ) {
		fdelete(curFile);
	}
}

bool EZLog::ifFileFull(const char* f) {
	int size = CPPTools::getFileSize(f);
	if( size > MAX_SIZE ) {
		return true;
	}
	return false;
}
bool EZLog::ifFileExist(const char* f) {
	return CPPTools::getFileSize(f) >= 0;
}

void EZLog::saveToFile(void) {
    FILE* f = fopen(curFile, "a");
    if( f ) {
        fprintf(f, "%d ", os_time_get());
        os_mut_wait(mut_log, 0xffff);	//存储期间保护临界资源
        for (int i = 0; i < bp; ++i) {
            fputs(BufOfLog[i].c_str(), f);
		}
        bp = 0;							//存储完毕后重置buf指针
        BufOfLog.clear();
        os_mut_release(mut_log);
        fputc('\n', f);
        fclose(f);
        if(ifFileFull(curFile)) {
        	switchCurrFile();
        }
    }

}

TASK void saveLog() {
    OS_RESULT result;
    bool needSave = false;
    while( 1 ) {
        result = os_evt_wait_or(0x0001, 1000);
        if( ((result == OS_R_TMO) && needSave) ||
        		EZLog::instance().bufFull() ) {
        	//系统在10秒没有新的日志产生，或者日志buf满的时候存储到文件
            EZLog::instance().saveToFile();
            needSave = false;
        }
        else if( result == OS_R_EVT ) {
            needSave = true;
        }
    }

}
