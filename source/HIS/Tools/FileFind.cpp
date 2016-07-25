/*
 * FileFind.cpp
 *
 *  Created on: 2016年6月16日
 *      Author: Administrator
 */

#include "FileFind.h"

FileFind::FileFind() {
    // TODO Auto-generated constructor stub

}

FileFind::~FileFind() {
    // TODO Auto-generated destructor stub
}

bool FileFind::getCfgFileInfoByID(uint16 id, FINFO& info) {
    char* mask = "*.cfg";
    info.fileID = 0;
    while( ffind (mask,&info) == 0 ) {
        if( id == info.fileID ) {
            return true;
        }
    }
    return false;
}

bool FileFind::getBitFileInfoByID(uint16 id, FINFO& info) {
    char* mask = "*.bit";
    info.fileID = 0;
    while( ffind (mask,&info) == 0 ) {
        if( id == info.fileID ) {
            return true;
        }
    }
    return false;

}
