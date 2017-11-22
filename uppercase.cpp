/*
 * uppercase.cpp
 *
 *  Created on: Apr 19, 2017
 *      Author: kjdorow
 */

#include "uppercase.h"
#include <string>
#include <algorithm>
#include <ctype.h>
using namespace std;

char upperCaseChar(char value) {
	char upVal = (char)toupper(value);
//	transform(value.begin(), value.end(), value.begin(), ::toupper);
	return upVal;
}

string upperCaseStr(string value) {
	transform(value.begin(), value.end(), value.begin(), ::toupper);
	return value;
}
