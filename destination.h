/*
 * destination.h
 *
 *  Created on: Nov 20, 2017
 *      Author: kjdorow
 */

#ifndef DESTINATION_H_
#define DESTINATION_H_


#include <string>
using namespace std;

class Destination {
	public://made public to make get it to work
		string destination;
		string write;
	public:
		Destination();
		string destination_state() const;
		void setDest(string dest);
		string write_string() const;
		void setWrite(string writeString);

};


#endif /* DESTINATION_H_ */
