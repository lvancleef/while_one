#include "instantaneous_description.h"
#include <string>
#include <iostream>
using namespace std;

        Instantaneous_Description::Instantaneous_Description(){

        }
        Instantaneous_Description::Instantaneous_Description(string initial_state, string input_string, char start_character, int level){
            current_state=initial_state;
            remaining_input_string=input_string;
            stack=start_character;
            current_level=level;
        }
        // void Instantaneous_Description::view() const{
        //     //where are we getting truncate from

        //     //int maximum_number_of_characters= configuration_settings_pointer->maximum_number_of_characters();
        //     //cout << "(" << current_state << "," << truncate(visble(remaining_input_string),maximum_number_of_characters)<< "," << truncate(visble(stack),maximum_number_of_characters);

        // }
        
        string Instantaneous_Description::state() const{
            return current_state;
        }
        char Instantaneous_Description::input_character() const{
            return remaining_input_string[0];
        }
        char Instantaneous_Description::top_of_stack() const{
            return stack[0];
        }
        bool Instantaneous_Description::is_empty_stack() const{
            return true;
        }
        bool Instantaneous_Description::is_empty_remaining_input_string() const{
            return true;
        }