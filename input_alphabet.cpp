/*
 * input_alphabet.cpp
 *
 *  Created on: Nov 16, 2017
 *      Author: kjdorow
 */

#include "uppercase.h"
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
//	string inAlphaLine;
//	getline(definition, inAlphaLine);
//
//	// check if INPUT_ALPHABET keyword exists
//	if (inAlphaLine.substr(0, 15).compare("INPUT_ALPHABET:") != 0) {
//		cout << "Error: Input_Alphabet Keyword is not present." << endl;
//		valid = false;
//		return;
//	}
//
//	// start looping at the first character
//	for (int i = 16; i < (int)inAlphaLine.length(); i++) {
//		if (isprint(inAlphaLine.at(i)) == 0) {
//			cout << "Error: Input Alphabet contains a non-printable character." << endl;
//			valid = false;
//			return;
//		}
//		alphabet.push_back(inAlphaLine.at(i));
//		// check if we are at the end
//		i++;
//		if (i >= (int)inAlphaLine.length()) {
//			break;
//		}
//		else {
//			// check if there is a space in between the characters
//			if (inAlphaLine.at(i) == ' ') {
//				continue;
//			}
//			else {
//				cout << "Error: Invalid Input Alphabet character." << endl;
//				valid = false;
//				return;
//			}
//		}
//	}
//	// Read in the blank line at the end of this section
//	getline(definition, inAlphaLine);
	alphabet.clear();
	string value;

	do {
		if ((definition >> value) and ( To_Upper(value) != "INPUT_ALPHABET:"))
		{
			if (To_Upper(value) == "STACK_ALPHABET:") {
				break;
			}
			for (int i = 0; i < (int)value.size(); i++)
			{
				if ((value[i] == '\\') or
						(value[i] == '[') or
						(value[i] == ']') or
						(value[i] == '<') or
						(value[i] == '>') or
						(value[i] <= '!') or
						(value[i] >= '~') or
						(isprint(value[i]) == 0))
				{
					valid = false;
					cout << "Character '" << value << "' within Input_Alphabet is invalid" << endl;
				}
			}
			for(int index=0;index<alphabet.size();index++)
                {
                    if(alphabet[index]==(value.at(0)))
                    {
                        cout<<"Error: Duplicate input alphabet character\n";
                        valid=false;
                    }
                }

			alphabet.push_back(value.at(0));
		}
		else if (To_Upper(value) == "STACK_ALPHABET:")
			break;

	} while (!definition.eof());

	if (definition.eof())
	{
		cout << "missing keyword STACK_ALPHABET: after INPUT_ALPHABET" << endl;
		valid = false;
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


