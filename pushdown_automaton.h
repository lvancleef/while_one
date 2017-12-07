#ifndef Pushdown_Automaton_H
#define Pushdown_Automaton_H
//#include "utility.h"
#include "input_alphabet.h"
#include "stack_alphabet.h"
#include "transition_function.h"
#include "states.h"
#include "final_states.h"
#include "instantaneous_description.h"
#include "configuration_settings.h"
#include "uppercase.h"
#include <string>
#include <algorithm>
#include <sstream>


using namespace std;

class Pushdown_Automaton{
private:
    Input_Alphabet input_alphabet;
    Stack_Alphabet stack_alphabet;
    Transition_Function transition_function;
    States states;
    Final_States final_states;
    Configuration_Settings *configuration_settings;

    vector<string> string_list;
    bool string_list_changed;
    int number_of_transitions;
    int number_of_transitions_performed;
    bool valid;
    bool used;
    bool running;
    bool accepted;
    bool rejected;
    bool changed;
    bool sorted;
    string initial_state;
    char start_character;
    int number_of_crashes;
    vector<string>accepted_path;

    string name;
    string original_input_string;
    string pda_description;

    //static Configuration_Setting_Pointer configuration_setting_pointer;
    
public:
    Pushdown_Automaton(Configuration_Settings *configuration_settings);
    Pushdown_Automaton();
    
    //static void Link(const Configuration_Settings configuration_settings);

    void load(string definition_file_name);
    void set_sort(bool value);
    bool pda_main();
    string perform_transition(Instantaneous_Description instantaneous_description, int &number_of_transitions_performed);
    bool is_accepted(Instantaneous_Description instantaneous_description);
    string commands();
    bool is_valid_input_string(string value);
    void print_id(Instantaneous_Description instantaneous_description);
    void initialize_string_list();
    void help_command();
    void show_command();
    void view_command();
    void list_command();
    void insert_command();
    void delete_command();
    void close_command();
    void quit_command();
    void sort_command();
    string truncate(string value);
    string visible(string value);
};

//typedef pushdown_automaton *pushdown_automaton;
#endif
