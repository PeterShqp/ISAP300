/*
 * EZLog.cpp
 *
 *  Created on: 2016年9月5日
 *      Author: Administrator
 */

#include "EZLog.h"
#include <stdio.h>

EZLog EZLog::log;

void EZLog::record(std::string& txt) {
    FILE* f = fopen("log.txt", "a");
    if( f ) {
        fputs(txt.c_str(), f);
        fputc('\n', f);
        fclose(f);
    }
}

void EZLog::record(const char* s) {
    FILE* f = fopen("log.txt", "a");
    if( f ) {
        fputs(s, f);
        fputc('\n', f);
        fclose(f);
    }

}
