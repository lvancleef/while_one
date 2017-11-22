/*
 * input_alphabet.cpp
 *
 *  Created on: Nov 16, 2017
 *      Author: kjdorow
 */

#include "input_alphabet.h"
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <ctype.h>
#include <iostream>
using namespace std;

Input_Alphabet::Input_Alphabet() {
	alphabet = vector<char>();
}

void Input_Alphabet::load(ifstream& definition, bool& valid) {
	string inAlphaLine;
	getline(definition, inAlphaLine);

	// check if INPUT_ALPHABET keyword exists
	if (inAlphaLine.substr(0, 15).compare("INPUT_ALPHABET:") != 0) {
		cout << "Error: Input_Alphabet Keyword is not present." << endl;
		valid = false;
		return;
	}

	// start looping at the first character
	for (int i = 16; i < (int)inAlphaLine.length(); i++) {
		if (isprint(inAlphaLine.at(i)) == 0) {
			cout << "Error: Input Alphabet contains a non-printable character." << endl;
			valid = false;
			return;
		}
		alphabet.push_back(inAlphaLine.at(i));
		// check if we are at the end
		i++;
		if (i >= (int)inAlphaLine.length()) {
			break;
		}
		else {
			// check if there is a space in between the characters
			if (inAlphaLine.at(i) == ' ') {
				continue;
			}
			else {
				cout << "Error: Invalid Input Alphabet character." << endl;
				valid = false;
				return;
			}
		}
	}
}

void Input_Alphabet::view() const {
	cout << "Input Alphabet: ";
	for (int i = 0; i < (int)alphabet.size(); i++) {
		cout << alphabet.at(i) << " ";
	}
	cout << endl;
}

bool Input_Alphabet::is_element(char value) const {
	// check if value is in Input Alphabet
	for (int i = 0; i < (int)alphabet.size(); i++) {
		if (value == alphabet.at(i)) {
			return true;
		}
	}
	return false;
}


