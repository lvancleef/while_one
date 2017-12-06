/*
 * transition_function.cpp
 *
 *  Created on: Nov 16, 2017
 *      Author: kjdorow
 */
#include "transition_function.h"
#include "stack_alphabet.h"
#include "states.h"
#include "final_states.h"
#include "uppercase.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <ctype.h>

using namespace std;

void Transition_Function::load(ifstream& definition, States states, Input_Alphabet input_alphabet, Stack_Alphabet stack_alphabet, bool& valid) {

	int count = 1;

	string value;
	int transIndex = 0;
	int vecSize = 10;
	transitions.resize(vecSize);

	do {

		if (count == 2 or count == 3) // read character and read stack
		{
			if ((definition >> value) &&
				(value.length() == 1) &&
				(value[0] != '[') &&
				(value[0] != ']') &&
				(value[0] != '<') &&
				(value[0] != '>') &&
				(value[0] >= '!') &&
				(value[0] <= '~') &&
				(value[0] != '(') &&
				(value[0] != ')') &&
				(value[0] != ','))
			{
				if (count == 2) {
					if (vecSize == transIndex) {
						vecSize = vecSize + 10;
						transitions.resize(vecSize);
					}
					transitions.at(transIndex).setRead(value[0]);
				}
				if (count == 3) {
					if (vecSize == transIndex) {
						vecSize = vecSize + 10;
						transitions.resize(vecSize);
					}
					transitions.at(transIndex).setReadStack(value[0]);
				}
			}
			else
			{
				cout << "in transition: invalid read character or read stack character: " << value << endl;
				valid = false;
			}
		}
		else if (count == 1 or count == 4)
		{
			if ((definition >> value) and ( To_Upper(value) != "INITIAL_STATE:"))
			{
				for (int i = 0; i < (int)value.size(); i++)
				{
					if ((value[i] == '[') or
						(value[i] == ']') or
						(value[i] == '<') or
						(value[i] == '>') or
						(value[i] <= '!') or
						(value[i] >= '~') or
						(value[i] == ')') or
						(value[i] == '(') or
						(value[i] == ','))
					{
						valid = false;
						cout << "in transition: invalid character '"<< value << "' within state" << endl;
					}
				}

				if (count == 1) {
					if (vecSize == transIndex) {
						vecSize = vecSize + 10;
						transitions.resize(vecSize);
					}
					transitions.at(transIndex).setSource(value);
				}
					//source_state = value;
				if (count == 4) {
					if (vecSize == transIndex) {
						vecSize = vecSize + 10;
						transitions.resize(vecSize);
					}
					transitions.at(transIndex).setDestState(value);
				}
					//destination_state = value;
			}
		}
		else if (count == 5)
		{
			if ((definition >> value))
			{
				for (int i = 0; i < (int)value.size(); i++)
				{
					if ((value[i] == '[') or
						(value[i] == ']') or
						(value[i] == '<') or
						(value[i] == '>') or
						(value[i] <= '!') or
						(value[i] >= '~') or
						(value[i] == ')') or
						(value[i] == '(') or
						(value[i] == ','))
					{
						valid = false;
						cout << "in transition: invalid character '"<< value << "' within state" << endl;
					}
				}

				if ((int)transitions.size() == transIndex) {
					vecSize = vecSize + 10;
					transitions.resize(vecSize);
				}
				transitions.at(transIndex).setWriteStr(value);
			}
			else
			{
				cout << "in transition: " <<  endl;
				valid = false;
			}
		}

		if (To_Upper(value) == "INITIAL_STATE:")
			break;

		if (count == 5)
		{
			if (!(states.is_element(transitions.at(transIndex).source_state()))) {
				cout << "Error: Transition Function contains a non-state." << endl;
				valid = false;
				return;
			}
			if (!(input_alphabet.is_element(transitions.at(transIndex).read_character())) &&
					transitions.at(transIndex).read_character() != '\\') {
				cout << "Error: Transition Function contains a character not from Input_Alphabet." << endl;
				valid = false;
				return;
			}
			if (!(stack_alphabet.is_element(transitions.at(transIndex).read_character_stack())) &&
					transitions.at(transIndex).read_character_stack() != '\\') {
				cout << "Error: Transition Function contains a character not from Stack_Alphabet." << endl;
				valid = false;
				return;
			}
			if (!(states.is_element(transitions.at(transIndex).destination_state()))) {
				cout << "Error: Transition Function contains a non-state." << endl;
				valid = false;
				return;
			}
			for (int j = 0; j < (int)transitions.at(transIndex).write_str().length(); j++) {
				if (!(stack_alphabet.is_element(transitions.at(transIndex).write_str().at(j))) &&
						transitions.at(transIndex).write_str().at(j) != '\\') {
					cout << "Error: Transition Function contains a character not from Stack_Alphabet." << endl;
					valid = false;
					return;
				}
			}

		}

		count++;
		if (count == 6){
			count = 1;
			transIndex++;
		}

	} while ( !definition.eof() );

	if (definition.eof())
	{
		cout << "missing keyword INITIAL_STATE: after transition function" << endl;
		valid = false;
	}

	transitions.resize(transIndex);
}

void Transition_Function::validate (const Stack_Alphabet& stack_alphabet,
		const Input_Alphabet& input_alphabet,
		const States& states,
		const Final_States& final_states,
		bool& valid) const {
	 for (int i = 0; i < (int)transitions.size(); i++) {
	 	if (final_states.Final_States::is_element(transitions[i].destination_state())) {
	 		cout << "Final State " << transitions[i].destination_state() << " is in final states." << endl;
	 		valid = false;
	 	}
	 	if (!states.States::is_element(transitions[i].source_state())) {
	 		cout << "Source State " << transitions[i].source_state() << " is not in states." << endl;
	 		valid = false;
	 	}
	 	if (!stack_alphabet.Stack_Alphabet::is_element(transitions[i].read_character_stack()) &&
	 			transitions[i].read_character_stack() != '\\') {
	 		cout << "Top of Stack Character " << transitions[i].read_character_stack() << "is not in stack alphabet." << endl;
	 		valid = false;
	 	}
	 	if (!states.States::is_element(transitions[i].destination_state())) {
	 		cout << "Destination State " << transitions[i].destination_state() << " is not in states." << endl;
	 		valid = false;
	 	}
//	 	if (!stack_alphabet.Stack_Alphabet::is_element(transitions[i].write_str().at(0)) &&
//	 			transitions[i].write_str().at(0) != '\\') {
//	 		cout << "Write String" << transitions[i].write_str() << " is not in stack alphabet." << endl;
//	 		valid = false;
//	 	}
		for (int j = 0; j < (int)transitions.at(i).write_str().length(); j++) {
			if (!(stack_alphabet.is_element(transitions.at(i).write_str().at(j))) &&
					transitions[i].write_str().at(j) != '\\') {
				cout << "Write String" << transitions[i].write_str() << " is not in stack alphabet." << endl;
				valid = false;
			}
		}
	 	if (!input_alphabet.Input_Alphabet::is_element(transitions[i].read_character()) &&
	 			transitions.at(i).read_character() != '\\') {
	 		cout << "Read Character" << transitions[i].read_character() << " is not in input alphabet." << endl;
	 		valid = false;
	 	}
	 }
}

void Transition_Function::view() const {
	cout << "Transitions: ";
	for (int i = 0; i < (int)transitions.size(); i++) {
		cout << endl;
		cout << "delta("<< transitions.at(i).source_state() << ", " << transitions.at(i).read_character() << ", "<<
				transitions.at(i).read_character_stack() << ") = ("
				<< transitions.at(i).destination_state() << ", "
				<< transitions.at(i).write_str() << ")";
	}
	cout<<endl;
}

void Transition_Function::find_transition(string source_state, char read_character,
	 	char read_stack_character, string& dest_state, string& write_stack, bool& found, int tried) const {
	 for (int i = 0; i < (int)transitions.size(); i++) {
	 	if ((transitions[i].source_state() == source_state) && (transitions[i].read_character() == read_character)
	 			&& (transitions[i].read_character_stack() == read_stack_character)) {
	 		if (tried == 1) {
	 			tried = 0;
	 			continue;
	 		}
	 		write_stack = transitions[i].write_str();
	 		dest_state = transitions[i].destination_state();
	 		found = true;
	 		return;
	 	}
	 }
	 found = false;
}





