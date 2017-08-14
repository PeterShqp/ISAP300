/*
 * SysError.h
 *
 *  Created on: 2013-11-20
 *      Author: Administrator
 */

#ifndef SYSERROR_H_
#define SYSERROR_H_

#include <stdexcept>
#include <string>

class SysError : public std::runtime_error {
public:
    SysError(const std::string& msg = "") : runtime_error(msg) {};
};

class ErrorNullPointer : public SysError {
public:
	ErrorNullPointer() : SysError("Null pointer") {};
};

class ErrorTooFast : public SysError {
public:
	ErrorTooFast() : SysError("Too fast") {};
};

class ErrorEthMemFull : public SysError {
public:
	ErrorEthMemFull() : SysError("Eth memory full") {};

};
#endif /* SYSERROR_H_ */
