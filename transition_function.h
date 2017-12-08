/*
 * transition_function.h
 *
 *  Created on: Nov 16, 2017
 *      Author: kjdorow
 */

#ifndef TRANSITION_FUNCTION_H_
#define TRANSITION_FUNCTION_H_

#include "transition.h"
#include "utility.h"
#include "states.h"
#include "final_states.h"
#include "input_alphabet.h"
#include "stack_alphabet.h"
#include "instantaneous_description.h"
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Transition_Function {
	private:
		vector<Transition> transitions;
	public:
		void load(ifstream& definition, States states, Input_Alphabet input_alphabet, Stack_Alphabet stack_alphabet, bool& valid);
		void validate(const Stack_Alphabet& stack_alphabet,
				const Input_Alphabet& input_alphabet,
				const States& states,
				const Final_States& final_states,
				bool& valid) const;
		void view();
		// pass by reference because they are output parameters
		bool find_transition(Instantaneous_Description &id, int tried) const;

    	string visible(string value);
};



#endif /* TRANSITION_FUNCTION_H_ */
