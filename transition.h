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
	private:
		string source;
		char read;
		char read_stack;
		//vector<Destination> destinations;
		string write_string;
		string dest_state;
	public:
		Transition();
		string source_state() const;
		void setSource(string state);
		char read_character() const;
		void setRead(char readChar);
		char read_character_stack() const;
		void setReadStack(char readStackChar);
		//vector<Destination> destination() const;
		string destination_state() const;
		void setDestState(string destState);
		string write_str() const;
		void setWriteStr(string writeStr);

};



#endif /* TRANSITION_H_ */
