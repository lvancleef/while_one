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
			
            if(value.length()>1){
            	cout<<"Error: Incorrect input character\n";
            	valid=false;
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
	if(valid){
		for(int i=0;i<alphabet.size()-1 ;i++){
			for(int index=i+1;index<alphabet.size();index++)
			{
			    if(alphabet[index]==alphabet[i])
			    {
			        cout<<"Error: Duplicate input character\n";
			        valid=false;
			    }
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


