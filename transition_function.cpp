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

void Transition_Function::load(ifstream& definition, Input_Alphabet input_alphabet, States states, Stack_Alphabet stack_alphabet, bool& valid) {

//	 string transitionLine;
//	 getline(definition, transitionLine);
//
//	 // check if TRANSITION_FUNCTION keyword exists
//	 if (transitionLine.substr(0, 20).compare("TRANSITION_FUNCTION:") != 0) {
//	 	cout << "Error: Transition_Function Keyword is not present." << endl;
//	 	valid = false;
//	 	return;
//	 }
//
//	 // loop through the transitions using line based parsing,
//	 // and string streams
//	 while (getline(definition, transitionLine)) {
//	 	if (transitionLine == "") {
//	 		break;
//	 	}
//	 	vector<string> transLines;
//	 	char* c = new char[transitionLine.length() + 1];
//	 	strcpy(c, transitionLine.c_str());
//
//	 	char* pch = strtok(c, " ");
//
//	 	// get the variables of the transition, and store them in a vector
//	 	while(pch != NULL) {
//	 		string s(pch);
//	 		transLines.push_back(s);
//	 		pch = strtok(NULL, " ");
//	 	}
//
//	 	delete []c;
//	 	// loop through the transLines vector and assign each element
//	 	// to the variables of the transitions vector
//	 	Transition transition;
//	 	int destVecIndex = 0;
//	 	if (transLines.size() < 5) {
//	 		cout << "Error: Transition line is invalid." << endl;
//	 		valid = false;
//	 		return;
//	 	}
//	 	else {
//	 		for (int i = 0; i < (int)transLines.size(); i++) {
//	 			// check if the first element of transLines is included in the
//	 			// list of states
//	 			if (!(states.is_element(transLines[i])) && i == 0) {
//	 				cout << "Error: Transition Function contains a non-state." << endl;
//	 				valid = false;
//	 				return;
//	 			}
//	 			else if (i == 0) {
//	 				transition.setSource(transLines[i]);
//	 				continue;
//	 			}
//	 			// check if the second element of transLines is included in the
//	 			// Input Alphabet
//	 			if (!(input_alphabet.is_element(transLines[i].at(0))) && i == 1) {
//	 				cout << "Error: Transition Function contains a character not from Input Alphabet." << endl;
//	 				valid = false;
//	 				return;
//	 			}
//	 			else if (i == 1) {
//	 				transition.setRead(transLines[i].at(0));
//	 				continue;
//	 			}
//	 			// check if the third element of transLines is included in the
//	 			// Stack Alphabet
//	 			if (!(stack_alphabet.is_element(transLines[i].at(0))) && i == 2) {
//	 				cout << "Error: Transition Function contains a character not from Stack Alphabet." << endl;
//	 				valid = false;
//	 				return;
//	 			}
//	 			else if (i == 2) {
//	 				transition.setReadStack(transLines[i].at(0));
//	 				continue;
//	 			}
//	 			// check if the fourth and fifth elements of transLines is included in the
//	 			// list of states and stack alphabet
//
//	 			if (!(states.is_element(transLines[i]))) {
//	 				cout << "Error: Transition Function contains a non-state." << endl;
//	 				valid = false;
//	 				return;
//	 			}
//	 			// need to check if the next element is included in the stack alphabet
//	 			i++;
//	 			if (!(stack_alphabet.is_element(transLines[i].at(0))) && i == 4) {
//	 				cout << "Error: Transition Function contains a character not from Stack Alphabet." << endl;
//	 				valid = false;
//	 				return;
//	 			}
//
//	 			transition.setDest(transLines[i-1], transLines[i], destVecIndex);
//	 			destVecIndex++;
//	 		}
//	 	}
//
//	 }
	int count = 1;

	string value;
	int transIndex = 0;

	do {

		if (count == 2 or count == 4) // read and write character
		{
			if ((definition >> value) &&
				(value.length() == 1) &&
				(value[0] != '\\') &&
				(value[0] != '[') &&
				(value[0] != ']') &&
				(value[0] != '<') &&
				(value[0] != '>') &&
				(value[0] >= '!') &&
				(value[0] <= '~'))
			{
				if (count == 2)
					transitions.at(transIndex).setRead(value[0]);
				if (count == 4)
					transitions.at(transIndex).setDestState(value);
			}
			else
			{
				cout << "in transition: invalid read or write character: " << value << endl;
				valid = false;
			}
		}
		else if (count == 1 or count == 3)
		{
			if ((definition >> value) and ( To_Upper(value) != "INITIAL_STATE:"))
			{
				for (int i = 0; i < (int)value.size(); i++)
				{
					if ((value[i] == '\\') or
						(value[i] == '[') or
						(value[i] == ']') or
						(value[i] == '<') or
						(value[i] == '>') or
						(value[i] <= '!') or
						(value[i] >= '~'))
					{
						valid = false;
						cout << "in transition: invalid character '"<< value << "'' within state";
					}
				}

				if (count == 1)
					transitions.at(transIndex).setSource(value);
					//source_state = value;
				if (count == 3)
					transitions.at(transIndex).setReadStack(value.at(0));
					//destination_state = value;
			}
		}
		else if (count == 5)
		{
			if ((definition >> value))
			{
				for (int i = 0; i < (int)value.size(); i++)
				{
					if ((value[i] == '\\') or
						(value[i] == '[') or
						(value[i] == ']') or
						(value[i] == '<') or
						(value[i] == '>') or
						(value[i] <= '!') or
						(value[i] >= '~'))
					{
						valid = false;
						cout << "in transition: invalid character '"<< value << "'' within state";
					}
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
			if (!(input_alphabet.is_element(transitions.at(transIndex).read_character()))) {
				cout << "Error: Transition Function contains a character not from Input_Alphabet." << endl;
				valid = false;
				return;
			}
			if (!(stack_alphabet.is_element(transitions.at(transIndex).read_character_stack()))) {
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
				if (!(stack_alphabet.is_element(transitions.at(transIndex).write_str().at(j)))) {
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
	 	if (!stack_alphabet.Stack_Alphabet::is_element(transitions[i].read_character_stack())) {
	 		cout << "Top of Stack Character " << transitions[i].read_character_stack() << "is not in stack alphabet." << endl;
	 		valid = false;
	 	}
	 	if (!states.States::is_element(transitions[i].destination_state())) {
	 		cout << "Destination State " << transitions[i].destination_state() << " is not in states." << endl;
	 		valid = false;
	 	}
	 	if (!stack_alphabet.Stack_Alphabet::is_element(transitions[i].write_str().at(0))) {
	 		cout << "Write String" << transitions[i].write_str() << " is not in stack alphabet." << endl;
	 		valid = false;
	 	}
	 	if (!input_alphabet.Input_Alphabet::is_element(transitions[i].read_character())) {
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
}

void Transition_Function::find_transition(string source_state, char read_character,
	 	char read_stack_character, string dest_state, string write_stack, bool& found) const {
	 for (int i = 0; i < (int)transitions.size(); i++) {
	 	if ((transitions[i].source_state() == source_state) && (transitions[i].read_character() == read_character)
	 			&& (transitions[i].read_character_stack() == read_stack_character)) {
	 		write_stack = transitions[i].write_str();
	 		dest_state = transitions[i].destination_state();
	 		found = true;
	 		return;
	 	}
	 }
	 found = false;
}

