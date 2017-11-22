/*
 * input_alphabet.h
 *
 *  Created on: Nov 16, 2017
 *      Author: kjdorow
 */

#ifndef INPUT_ALPHABET_H_
#define INPUT_ALPHABET_H_

#include <vector>
#include <fstream>
using namespace std;

class Input_Alphabet {
	private:
		vector<char> alphabet;
	public:
		Input_Alphabet();
		void load(ifstream& definition, bool& valid);
		void view() const;
		bool is_element(char value) const;
};


#endif /* INPUT_ALPHABET_H_ */
