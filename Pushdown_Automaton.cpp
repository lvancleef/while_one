#include "input_alphabet.h"
#include "stack_alphabet.h"
#include "transition_function.h"
#include "states.h"
#include "final_states.h"
#include "instantaneous_description.h"
#include "configuration_settings.h"

#include <string>

using namespace std;

Pushdown_Automaton::Pushdown_Automaton()
{
}

bool Pushdown_Automaton::is_accepted(Instantaneous_Description instantaneous_description, int number_in_current_path)
{
    return true;
}

void Pushdown_Automaton::load(string definition_file_name)
{
}

bool Pushdown_Automaton::PDA_main(Configuration_Settings configuration_settings)
{
    return true;
}

string Pushdown_Automaton::perform_transition(Instantaneous_Description instantaneous_description, int &number_of_transitions_performed)
{
    if(number_of_transitions_performed == config_settings.get_maximum_transitions())
    {
        return true; 
    }

    perform_transition(instantaneous_description, number_of_transitions_performed++);
    
    return false;
}

bool Pushdown_Automaton::is_accepted(Instantaneous_Description instantaneous_description, int number_in_current_path)
{
    return true;
}

void Pushdown_Automaton::commands()
{
//command loop
}
    
bool Pushdown_Automaton::is_valid_input_string(string value)
{
    return true;
}

void Pushdown_Automaton::print_id(Instantaneous_Description instantaneous_description)
{
    cout<<"ID\n";

    return;
}

void Pushdown_Automaton::initialize_string_list()
{
    return;
}
    
void Pushdown_Automaton::help_command()
{
    cout<<"help command\n";
}

void Pushdown_Automaton::show_command()
{
    cout<<"show command\n";
}

void Pushdown_Automaton::view_command()
{
    cout<<"view command\n";
}
    
void Pushdown_Automaton::list_command()
{
    cout<<"list command\n";
}

void Pushdown_Automaton::insert_command()
{
    cout<<"insert command\n";
}

// note from lvancleef
// does this really take in a value, or are we asking
// within the command
void Pushdown_Automaton::delete_command(int value)
{
    cout<<"del command\n";
}

void Pushdown_Automaton::sort_command()
{
    cout<<"sort command\n";
}

void Pushdown_Automaton::set_command()
{
    cout<<"set command\n";
    }
    
void Pushdown_Automaton::close_command()
{
    cout<<"close command\n";
}

