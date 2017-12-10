/*
* transition_function.cpp
*
*  Created on: Nov 16, 2017
*      Author: kjdorow
*/
#include "debug.h"
#include "transition_function.h"
#include "stack_alphabet.h"
#include "states.h"
#include "final_states.h"
#include "uppercase.h"
#include "instantaneous_description.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <ctype.h>


using namespace std;

void Transition_Function::load(ifstream& definition, States states, Input_Alphabet input_alphabet, Stack_Alphabet stack_alphabet, bool& valid) {
	char empty_char = '\0';
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
					if (value[0] == '\\') {
						transitions.at(transIndex).setRead(empty_char);
					}
					else {
						transitions.at(transIndex).setRead(value[0]);
					}
				}
				if (count == 3) {
					if (vecSize == transIndex) {
						vecSize = vecSize + 10;
						transitions.resize(vecSize);
					}
					if (value[0] == '\\') {
						transitions.at(transIndex).setReadStack(empty_char);
					}
					else {
						transitions.at(transIndex).setReadStack(value[0]);
					}
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
			if ((definition >> value) and(To_Upper(value) != "INITIAL_STATE:"))
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
						cout << "in transition: invalid character '" << value << "' within state" << endl;
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
						cout << "in transition: invalid character '" << value << "' within write string" << endl;
					}
				}

				if ((int)transitions.size() == transIndex) {
					vecSize = vecSize + 10;
					transitions.resize(vecSize);
				}
				if (value == "\\") {
					transitions.at(transIndex).setWriteStr("");
				}
				else {
					transitions.at(transIndex).setWriteStr(value);
				}
			}
			else
			{
				cout << "in transition: " << endl;
				valid = false;
			}
		}

		if (To_Upper(value) == "INITIAL_STATE:")
			break;

		if (count == 5)
		{
			if (!(states.is_element(transitions.at(transIndex).source_state()))) {
				cout << "Error: Transition Function contains a non-state." << transitions.at(transIndex).source_state() << endl;
				valid = false;
				return;
			}
			if (!(input_alphabet.is_element(transitions.at(transIndex).read_character())) &&
				transitions.at(transIndex).read_character() != empty_char) {
				cout << "Error: Transition Function contains a character not from Input_Alphabet:" << transitions.at(transIndex).read_character() << endl;
				valid = false;
				return;
			}
			if (!(stack_alphabet.is_element(transitions.at(transIndex).read_character_stack())) &&
				transitions.at(transIndex).read_character_stack() != empty_char) {
				cout << "Error: Transition Function contains a character not from Stack_Alphabet:" << transitions.at(transIndex).read_character_stack() << endl;
				valid = false;
				return;
			}
			if (!(states.is_element(transitions.at(transIndex).destination_state()))) {
				cout << "Error: Transition Function contains a non-state:" << transitions.at(transIndex).destination_state() << endl;
				valid = false;
				return;
			}
			for (int j = 0; j < (int)transitions.at(transIndex).write_str().length(); j++) {
				if (!(stack_alphabet.is_element(transitions.at(transIndex).write_str().at(j))) &&
					transitions.at(transIndex).write_str().at(j) != empty_char) {
					cout << "Error: Transition Function contains a character not from Stack_Alphabet:" << transitions.at(transIndex).write_str().at(j) << endl;
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

	} while (!definition.eof());

	if (definition.eof())
	{
		cout << "missing keyword INITIAL_STATE: after transition function" << endl;
		valid = false;
	}

	transitions.resize(transIndex);
}

void Transition_Function::validate(const Stack_Alphabet& stack_alphabet,
	const Input_Alphabet& input_alphabet,
	const States& states,
	const Final_States& final_states,
	bool& valid) const {
	char empty_char = '\0';
	for (int i = 0; i < (int)transitions.size(); i++) {
		if (final_states.Final_States::is_element(transitions[i].destination_state())) {
			cout << "Final State " << transitions[i].destination_state() << " is not in final states." << endl;
			valid = false;
		}
		if (!states.States::is_element(transitions[i].source_state())) {
			cout << "Source State " << transitions[i].source_state() << " is not in states." << endl;
			valid = false;
		}
		if (!stack_alphabet.Stack_Alphabet::is_element(transitions[i].read_character_stack()) &&
			transitions[i].read_character_stack() != empty_char) {
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
				transitions[i].write_str().at(j) != empty_char) {
				cout << "Write String" << transitions[i].write_str() << " is not in stack alphabet." << endl;
				valid = false;
			}
		}
		if (!input_alphabet.Input_Alphabet::is_element(transitions[i].read_character()) &&
			transitions.at(i).read_character() != empty_char) {
			cout << "Read Character" << transitions[i].read_character() << " is not in input alphabet." << endl;
			valid = false;
		}
	}
}

void Transition_Function::view() const {
	string read;
	cout << "Transitions: ";
	for (int i = 0; i < (int)transitions.size(); i++) {
		read = "";
		if (transitions.at(i).read_character() != '\0')
			read.push_back(transitions.at(i).read_character());

		cout << endl;
		cout << "delta(" << transitions.at(i).source_state() << ", " << visible(read) << ", " <<
			transitions.at(i).read_character_stack() << ") = ("
			<< transitions.at(i).destination_state() << ", "
			<< visible(transitions.at(i).write_str()) << ")";
	}
	cout << endl;
}

bool Transition_Function::find_transition(Instantaneous_Description &id, int tried) const {
	for (int i = 0; i < (int)transitions.size(); i++) {

		// if(DEBUG){
		// 	if(id.get_current_state()=="s1"){
		// 		cout<<id.get_current_state()<<"="<<transitions[i].source_state()<<endl;
		// 		cout<<id.input_character()<<"="<<transitions[i].read_character()<<endl;
		// 		cout<<id.top_of_stack()<<"="<<transitions[i].read_character_stack()<<endl;
		// 	}


		//}

		if ((transitions[i].source_state() == id.get_current_state()) && (transitions[i].read_character() == id.input_character())
			&& (transitions[i].read_character_stack() == id.top_of_stack())) {
			if (tried != 0) {
				tried--;

				continue;
			}

			id.set_current_stack(transitions[i].write_str());
			id.set_current_state(transitions[i].destination_state());
			return true;
		}
	}
	return false;
}


string Transition_Function::visible(string value){
	const string lambda("\\");
	if (value.empty())
		value = lambda;
	return value;
}
