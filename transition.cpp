/*
 * transition.cpp
 *
 *  Created on: Nov 16, 2017
 *      Author: kjdorow
 */
#include "transition.h"
#include "destination.h"
#include <string>
#include <vector>
using namespace std;

Transition::Transition() {
	source = "";
	read = ' ';
	read_stack = ' ';
	write_string = "";
	dest_state = "";
}

string Transition::source_state() const {
	return source;
}

void Transition::setSource(string state) {
	this->source = state;
}

char Transition::read_character() const {
	return read;
}

void Transition::setRead(char readChar) {
	this->read = readChar;
}

char Transition::read_character_stack() const {
	return read_stack;
}

void Transition::setReadStack(char readCharStack) {
	this->read_stack = readCharStack;
}

//vector<Destination> Transition::destination() const{
//	return destinations;
//}

string Transition::destination_state() const {
	return dest_state;
}

void Transition::setDestState(string destState) {
	this->dest_state = destState;
}

string Transition::write_str() const {
	return write_string;
}

void Transition::setWriteStr(string writeStr) {
	this->write_string = writeStr;
}


