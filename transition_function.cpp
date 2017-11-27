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
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <ctype.h>

#include "uppercase.h"
using namespace std;

void Transition_Function::load(ifstream& definition, Input_Alphabet input_alphabet, States states, Stack_Alphabet stack_alphabet, bool& valid) {

	 string transitionLine;
	 getline(definition, transitionLine);

	 // check if TRANSITION_FUNCTION keyword exists
	 if (transitionLine.substr(0, 20).compare("TRANSITION_FUNCTION:") != 0) {
	 	cout << "Error: Transition_Function Keyword is not present." << endl;
	 	valid = false;
	 	return;
	 }

	 // loop through the transitions using line based parsing,
	 // and string streams
	 while (getline(definition, transitionLine)) {
	 	if (transitionLine == "") {
	 		break;
	 	}
	 	vector<string> transLines;
	 	char* c = new char[transitionLine.length() + 1];
	 	strcpy(c, transitionLine.c_str());

	 	char* pch = strtok(c, " ");

	 	// get the variables of the transition, and store them in a vector
	 	while(pch != NULL) {
	 		string s(pch);
	 		transLines.push_back(s);
	 		pch = strtok(NULL, " ");
	 	}

	 	delete []c;
	 	// loop through the transLines vector and assign each element
	 	// to the variables of the transitions vector
	 	Transition transition;
	 	int destVecIndex = 0;
	 	if (transLines.size() < 5) {
	 		cout << "Error: Transition line is invalid." << endl;
	 		valid = false;
	 		return;
	 	}
	 	else {
	 		for (int i = 0; i < (int)transLines.size(); i++) {
	 			// check if the first element of transLines is included in the
	 			// list of states
	 			if (!(states.is_element(transLines[i])) && i == 0) {
	 				cout << "Error: Transition Function contains a non-state." << endl;
	 				valid = false;
	 				return;
	 			}
	 			else if (i == 0) {
	 				transition.setSource(transLines[i]);
	 				continue;
	 			}
	 			// check if the second element of transLines is included in the
	 			// Input Alphabet
	 			if (!(input_alphabet.is_element(transLines[i].at(0))) && i == 1) {
	 				cout << "Error: Transition Function contains a character not from Input Alphabet." << endl;
	 				valid = false;
	 				return;
	 			}
	 			else if (i == 1) {
	 				transition.setRead(transLines[i].at(0));
	 				continue;
	 			}
	 			// check if the third element of transLines is included in the
	 			// Stack Alphabet
	 			if (!(stack_alphabet.is_element(transLines[i].at(0))) && i == 2) {
	 				cout << "Error: Transition Function contains a character not from Stack Alphabet." << endl;
	 				valid = false;
	 				return;
	 			}
	 			else if (i == 2) {
	 				transition.setReadStack(transLines[i].at(0));
	 				continue;
	 			}
	 			// check if the fourth and fifth elements of transLines is included in the
	 			// list of states and stack alphabet

	 			if (!(states.is_element(transLines[i]))) {
	 				cout << "Error: Transition Function contains a non-state." << endl;
	 				valid = false;
	 				return;
	 			}
	 			// need to check if the next element is included in the stack alphabet
	 			i++;
	 			if (!(stack_alphabet.is_element(transLines[i].at(0))) && i == 4) {
	 				cout << "Error: Transition Function contains a character not from Stack Alphabet." << endl;
	 				valid = false;
	 				return;
	 			}

	 			transition.setDest(transLines[i-1], transLines[i], destVecIndex);
	 			destVecIndex++;
	 		}
	 	}

	 }
}

void Transition_Function::validate (const Stack_Alphabet& stack_alphabet,
		const Input_Alphabet& input_alphabet,
		const States& states,
		const Final_States& final_states,
		bool& valid) const {
	int destVectIndex = 0;
	 for (int i = 0; i < (int)transitions.size(); i++) {
	 	if (final_states.Final_States::is_element(transitions[i].source_state())) {
	 		cout << "Source State " << transitions[i].source_state() << " is in final states." << endl;
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
	 	if (!states.States::is_element(transitions[i].destination()[destVectIndex].destination_state())) {
	 		cout << "Destination State " << transitions[i].destination()[destVectIndex].destination_state() << " is not in states." << endl;
	 		valid = false;
	 	}
	 	if (!stack_alphabet.Stack_Alphabet::is_element(transitions[i].destination()[destVectIndex].write_string().at(0))) {
	 		cout << "Write String" << transitions[i].destination()[destVectIndex].write_string() << " is not in stack alphabet." << endl;
	 		valid = false;
	 	}
	 	if (!input_alphabet.Input_Alphabet::is_element(transitions[i].read_character())) {
	 		cout << "Read Character" << transitions[i].read_character() << " is not in input alphabet." << endl;
	 		valid = false;
	 	}
	 	destVectIndex++;
	 }
}

void Transition_Function::view() const {
	int destVectIndex = 0;
	cout << "Transitions: ";
	for (int i = 0; i < (int)transitions.size(); i++) {
		cout << endl;
		cout << "delta("<< transitions.at(i).source_state() << ", " << transitions.at(i).read_character() << ", "<<
				transitions.at(i).read_character_stack() << ") = ("
				<< transitions.at(i).destination()[destVectIndex].destination_state() << ", "
				<< transitions.at(i).destination()[destVectIndex].write_string() << ")";
		destVectIndex++;
	}
}

void Transition_Function::find_transition(string source_state, char read_character,
	 	char read_stack_character, vector<Destination> destinations, bool& found) const {
	 for (int i = 0; i < (int)transitions.size(); i++) {
	 	if ((transitions[i].source_state() == source_state) && (transitions[i].read_character() == read_character)
	 			&& (transitions[i].read_character_stack() == read_stack_character)) {
	 		destinations = transitions[i].destination();
	 		found = true;
	 		return;
	 	}
	 }
	 found = false;
}

