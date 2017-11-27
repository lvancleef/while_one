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
	destinations = vector<Destination>();
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

vector<Destination> Transition::destination() const{
	return destinations;
}


void Transition::setDest(string destState, string writeStr, int index) {
	this->destinations.at(index).destination = destState; //this doesnt work if destination is prvate
	this->destinations.at(index).write = writeStr; //this doesnt work if destination is prvate
}


