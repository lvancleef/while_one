/*
 * destination.cpp
 *
 *  Created on: Nov 20, 2017
 *      Author: kjdorow
 */
#include "destination.h"
#include <string>
using namespace std;

Destination::Destination() {
	destination = "";
	write = "";
}

string Destination::destination_state() const {
	return destination;
}

void Destination::setDest(string dest) {
	this->destination = dest;
}

string Destination::write_string() const {
	return write;
}

void Destination::setWrite(string writeStr) {
	this->write = writeStr;
}

