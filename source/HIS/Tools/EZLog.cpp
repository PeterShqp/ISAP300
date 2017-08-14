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

void EZLog::record(std::string& txt) {
	record(txt.c_str());
}

void EZLog::record(const char* s) {
    os_mut_wait(mut_log, 0xffff);
    FILE* f = fopen(curFile, "a");
    if( f ) {
        fprintf(f, "%d ", os_time_get());
        fputs(s, f);
        fputc('\n', f);
        fclose(f);
        if(ifFileFull(curFile)) {
        	switchCurrFile();
        }
    }
    os_mut_release(mut_log);
}

void EZLog::init(void) {
    os_mut_init(mut_log);
    MAX_SIZE = 6000;
    findActiveFile();
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
