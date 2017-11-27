/*
 * transition.h
 *
 *  Created on: Nov 16, 2017
 *      Author: kjdorow
 */

#ifndef TRANSITION_H_
#define TRANSITION_H_

#include <string>
#include <vector>
#include "destination.h"
using namespace std;

class Transition {
	public: // temp to get get it to compile we need to fix access private variables
		string source;
		char read;
		char read_stack;
		vector<Destination> destinations;
	public:
		Transition();
		string source_state() const;
		void setSource(string state);
		char read_character() const;
		void setRead(char readChar);
		char read_character_stack() const;
		void setReadStack(char readStackChar);
		vector<Destination> destination() const;
		void setDest(string destState, string writeStr, int index);

};



#endif /* TRANSITION_H_ */
