#include "pushdown_automaton.h"
//#include "utility.h"
#include "input_alphabet.h"
#include "stack_alphabet.h"
#include "transition_function.h"
#include "states.h"
#include "final_states.h"
#include "instantaneous_description.h"
#include "configuration_settings.h"
#include "uppercase.h"
#include "debug.h"

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

Pushdown_Automaton::Pushdown_Automaton(Configuration_Settings *config_settings)//sets the pointer to configuration_settings
{
    configuration_settings=config_settings;
}

bool Pushdown_Automaton::is_accepted(Instantaneous_Description id)//takes a instantaneous_description and return true if it is accepted, false if it is negative
{
    if(!final_states.is_element(id.get_current_state())||!id.is_empty_remaining_input_string()||!id.is_empty_stack()){
        
        return false;
    }   
    else{

        return true;
    }

}

void Pushdown_Automaton::load(string definition_file_name)
//loads a new pda and calls the load methods a the other calls in order, by taking in the file name as a string, if a pda is invalid valid is set to false
{
    name="";
    changed=false;
    string_list.clear();
    number_of_crashes=0;
    number_of_transitions=0;
    number_of_transitions_performed=0;
    valid=true;
    running=false;
    string def_file=definition_file_name;
    name=definition_file_name;

    def_file+=".def";
    ifstream definition,string_file;
    definition.open(def_file.c_str());   
    if(definition.fail()){
        cout<<"File does not exist\n";
        valid=false;
        return;
    }
    else{
        pda_description="";
        valid=true;
        used=false;
        running=false;
        accepted=false;
        rejected=false;
        string keyword;
        number_of_transitions=0;
        number_of_transitions_performed=0;
         
        while(1)
        {
            if(definition>>keyword)
            {             
                if(To_Upper(keyword)=="STATES:")
                {
                    break;
                }
                else
                {
                    pda_description+=" ";
                    pda_description+=keyword;
                }
            }
            else {
                valid=false;
                cout<<"ERROR: States is missing\n";
                valid=false;
            }
        }
        states.load(definition, valid);
        input_alphabet.load(definition, valid);
        stack_alphabet.load(definition, valid);
        transition_function.load(definition, states, input_alphabet, stack_alphabet, valid);
        definition>>keyword;

        initial_state=keyword;
        
        if(!states.is_element(initial_state)){
            cout<<"Initial State is not part of states\n";
            valid=false;
        }
        //validate initial_state here
        definition>>keyword;
        
        if((To_Upper(keyword)!="START_CHARACTER:")){
            cout<<"START_CHARACTER is missing\n";
            valid=false;
        }
        else{
            definition>>keyword;
            if(keyword.length()==1){
                
                start_character=keyword[0];
                if(!stack_alphabet.is_element(start_character)){
                    cout<<"Start character is not part of stack alphabet\n";
                    valid=false;
                }
            }
        }
        definition>>keyword;
        if((To_Upper(keyword)!="FINAL_STATES:")){
            cout<<"FINAL_STATES is missing\n";
            valid=false;
        }
        final_states.load(definition, valid);
        final_states.validate(states, valid);
        definition.close();
    }

    initialize_string_list();
    string_file.close();
}

bool Pushdown_Automaton::pda_main()//verifies a pda is valid handles output from commands while pda is open 
{
    ostringstream oss;
    string command;
    string run;
    if(!valid){
        cout<<"Invalid PDA\n";
        return false;
    }
    else if (valid){
        cout<<"PDA successfully loaded\n";
    }
while(1){        
        command=commands();
        if(command.empty()){}
        else if(command=="open"){
            if(running){
                quit_command();
            }
            close_command();
            return true;
        }
        else if(command=="quit"){
            if(running){
                quit_command();
            }
            else{
                cout<<"No PDA running\n";
            }
        }
        else if(command=="close"){
            close_command();
            return false;
        }
        else if(command=="exit"){
            close_command();
            configuration_settings->exit_command();
        }
        else if(command=="run"){
            bool valid_run_string=true;
            int input_num;
            accepted_path.clear();
            oss.str("");
            
            cout<<"Input string number: ";
            string load="";
            
            getline(cin,load);

            if(load!=""){
                if(istringstream ( load ) >> input_num){
                    if(input_num<1 or input_num>string_list.size())
                        {
                            cout<<"Index out of range\n";
                            valid_run_string=false;
                            
                        }
                        else{
                            original_input_string=string_list[input_num-1];
                            used=true;
                            running=true;
                            number_of_transitions=0;
                            number_of_crashes=0;
                            
                        }
                }
                else{
                    cout<<"Invalid Input\n";
                    valid_run_string=false;   
                }
                            
                if(valid_run_string){
                    string start_character_string;
                    stringstream ss;
                    ss.str("");
                    ss<< start_character;
                    ss>> start_character_string;
                    string id_string;
                    Instantaneous_Description id(initial_state, original_input_string, start_character_string, 0);
                    
                    print_id(id);
                    run=perform_transition(id, number_of_transitions_performed);

                    if(run=="accepted"){             
                         
                        oss<<"["<<id.get_current_level()<<"] (";
                        oss<<id.get_current_state()<<",";
                        oss<<truncate(visible(id.get_remaining_input_string()))<<",";
                        oss<<truncate(visible(id.get_stack()))<<")\n";
                        id_string=oss.str();
                        
                        accepted_path.push_back(id_string);
                        
                        cout<<original_input_string<<" was accepted in "<<number_of_transitions<<" transitions\n";
                        cout<<"With "<<number_of_crashes<<" crashes\n";
                        accepted=true;
                        if(configuration_settings->get_complete_paths()){
                            cout<<"Accepted path:\n";
                            while(accepted_path.size() > 0)
                            {    
                                cout << accepted_path.back();     
                                accepted_path.pop_back();              
                            }
                            
                        }
                        running=false;
                        number_of_transitions_performed = 0;
                    } 
                    else if(run=="rejected"){
                        cout<<original_input_string<<" was rejected in "<<number_of_transitions<<" transitions\n";
                        cout<<"With "<<number_of_crashes<<" crashes\n";
                        running=false;
                        rejected=true;
                        number_of_transitions_performed = 0;
                    }
                    else if(run=="close"){
                            
                            close_command();
                            
                            return false;
                    }
                    else if(run=="quit"){
                        if(running){
                            number_of_transitions_performed = 0;
                            quit_command();
                        }
                        else{
                            cout<<"Not currently running on an input string" << endl;
                        }
                    }
                    else if(run=="open"){
                        
                            close_command();
                        
                       return true;
                    }
                    else if(run=="exit"){
                        
                        close_command();
                        
                    return false;    
                    }
                }
            }
        }
    }
}

string Pushdown_Automaton::perform_transition(Instantaneous_Description instantaneous_description, int &number_of_transitions_performed)
{//this function checks if a instanenous description is accepted and find and performs a new transition if avaible and calls perform transition again, if no transitions are aviable the function returns rejected to the function that called it
    //the main recussion and operating on pda happens because of this function
    Instantaneous_Description next_id;   
    int tried = 0;
    string command;
    string transition;
    string id_string;
    ostringstream oss;

    while(1)
    {
        if( is_accepted(instantaneous_description) )
        {
           if(!configuration_settings->get_complete_paths())
            {
                print_id(instantaneous_description);
            } 
            return "accepted";
        }
        
        next_id = instantaneous_description;
        next_id.increment_level();

        if(number_of_transitions_performed == configuration_settings->get_maximum_transitions())
        {
           
            if(!configuration_settings->get_complete_paths())
            {
                print_id(instantaneous_description);
            } 

            command = commands();

            if(command != "run")
                return command;

            number_of_transitions_performed = 0;
        }
        
        if(!transition_function.find_transition(next_id, tried))
        {
            
            if(configuration_settings->get_complete_paths())
            {
                cout << "Crash" << endl;    
            }

            number_of_crashes++;

            return "rejected";
        }
        
        number_of_transitions++;
        next_id.next_transition();
     
        if(configuration_settings->get_complete_paths())
        {
            print_id(next_id);
        }    

        transition = perform_transition(next_id, ++number_of_transitions_performed);

        if(transition!="rejected")
        {
            if(transition=="accepted")
            {
            
                oss << "[" << next_id.get_current_level() << "] (";
                oss << next_id.get_current_state() << ",";
                oss << truncate(visible(next_id.get_remaining_input_string())) << ",";
                oss << truncate(visible(next_id.get_stack())) << ")\n";
                id_string = oss.str();

                accepted_path.push_back(id_string);
            }

            return transition;
        }

        tried++;

    }
}

string Pushdown_Automaton::commands()//accepts user input while a pda is open
{
    int failed=0;
    int exit;
    string Command ="";
//command loop
    do{
        cout<<"Command: ";
        getline(cin, Command);   
            if(Command.length()>1){
                cout<<"Please only enter one character\n";
                failed++;
            }
            else if (Command == "c" || Command == "C"){
                failed=0;
                return "close";
            }   
            else if(Command == "d"||Command== "D"){
                failed=0;
                delete_command();
            }
            else if(Command == "p"||Command == "P"){   
                failed=0;
                configuration_settings->display_command();            
            }   
            else if(Command == "x"||Command== "X"){
                failed=0;
                close_command();
                configuration_settings->exit_command();
            }      
            else if(Command == "H" || Command== "h"){   
                failed=0;
                help_command();
            }
            else if(Command == "I" || Command== "i"){
                failed=0;
                insert_command();
            }              
            else if(Command == "L" || Command== "l"){
                failed=0;
                list_command();
            }
            else if(Command=="Q"||Command=="q"){
                failed=0;
                return "quit";
            }
            else if(Command=="o"||Command=="O"){
                failed=0;
                return "open";
            }                
            else if(Command == "R" ||Command== "r"){
                failed=0;
                return "run";
            }               
            else if(Command == "e" || Command== "E"){
                failed=0;
                 configuration_settings->set_command();
            }               
            else if(Command == "W" || Command== "w"){
                failed=0;
                show_command();
            }
            else if(Command == "S"|| Command == "s"){
                failed=0;
                sort_command();
            }   
            else if(Command == "T" || Command == "t"){         
                failed=0;      
                 configuration_settings->truncate_command();
            }               
            else if(Command == "V" || Command == "v"){
                failed=0;
                view_command();
            }
            else if(Command.empty())
            {}          
            else if (failed >= 5)
			{	
				cout << "Too many invalid selections. Exiting." << endl;
				configuration_settings->exit_command();
			}
			else{
                failed++;
                cout << "Please enter a valid character. 'H' provides a list." << endl;
            }
		
    }while (exit!=1);
    return "exit";
}
    
bool Pushdown_Automaton::is_valid_input_string(string value)//validates a input string
{
    bool flag=true;
    for(int index=0;index<string_list.size();index++){
        if(string_list[index]==value)
        {
            cout<<"That string already exists\n";
            flag=false;
        } 
    }
    if(value!="\\"&&flag==true){
   
        for(int index=0;index<value.length();index++){
            if(!input_alphabet.is_element(value[index])){
                //cout<<"Invalid character: "<<value[index]<<;
                return false;
            }
        }
    }                           
    return flag;
}

void Pushdown_Automaton::print_id(Instantaneous_Description instantaneous_description)//prints an instanenous description
{
    cout << "[" << number_of_transitions << "]. [" << instantaneous_description.get_current_level() << "] (";
    cout << instantaneous_description.get_current_state() << ",";
    cout << truncate(visible(instantaneous_description.get_remaining_input_string())) << ",";
    cout << truncate(visible(instantaneous_description.get_stack())) << ")\n";
}

void Pushdown_Automaton::initialize_string_list()//reads the .str file of the pda, validates and loads input string into the string list
{
    ifstream strstream;
    string load;
    string String_File=name;
    String_File+=".str";
    strstream.open(String_File.c_str());///error checking for bad strings
            
    if (strstream.is_open()) 
    {           
        while (getline(strstream, load))
            {bool flag=true;
                if(load==""){
                    cout<<"Blank line, for empty string use \\ \n";
                    changed=true;
                    flag=false;
                }
                else if(load=="\\")
                    {
                        for(int index=0;index<string_list.size();index++)
                        {
                            if(string_list[index]=="\\")
                            {
                                flag=false;
                            }
                        }
                        if(flag!=false)
                        {
                            string_list.push_back("\\");
                        }
                    }
                    else
                    {
                        for(int index=0;index<string_list.size();index++)
                            {
                                if(string_list[index]==load)
                                {
                                    cout<<"That string already exists\n";
                                    flag=false;
                                }
                            }
                                                       
                        for(int index=0;index<load.length();index++)
                        {
                            if(is_valid_input_string(load)==false)
                            {
                                
                                cout<<"Invalid input string\n";
                                flag=false;
                                changed=true;
                                break;
                            }
                        }
                        if(flag==true)
                        string_list.push_back(load);
                    }
            }
    }
    else 
    {
        cout<<"No '.str' file found\nPlease input string with the [I]nsert Command\n";
    }
}
    
void Pushdown_Automaton::help_command()//prints the help display
{
    cout<<"[C]lose\t\tClose pushdown automaton\n";
    cout<<"[D]elete\tDelete input string from list\n";
    cout<<"Dis[p]lay\tComplete paths through pushdown automaton\n";
    cout<<"E[x]it\t\tExit application\n";
    cout<<"[H]elp\t\tHelp User\n";
    cout<<"[I]nsert\tInsert input string into list\n";
    cout<<"[L]ist\t\tDisplay list of input strings\n";
    cout<<"[O]pen\t\tOpen pushdown automaton\n";
    cout<<"[Q]uit\t\tQuit operation of PDA on input string\n"; 
    cout<<"[R]un\t\tRun PDA on input string\n";
    cout<<"S[e]t\t\tSet maximum number of transitions\n";
    cout<<"Sho[w]\t\tShow status of application\n";
    cout<<"[S]ort\t\tSort input strings in canonical order\n";
    cout<<"[T]runcate\tTruncate instantaneous description\n";
    cout<<"[V]iew\t\tView pushdown automaton\n";
}

void Pushdown_Automaton::show_command()//determines state of open pda print correct show details
 
    cout<<"  Name of PDA:\t"<<name<<endl;

    if(running){      
        cout<<"  Status:\tPDA is currently running on an input string\n";     
        cout<<"  Input string:\t"<<original_input_string<<endl;
        cout<<"  Transitions:\t"<<number_of_transitions<<endl;
        cout<<"  Crashes:\t"<<number_of_crashes<<endl;
    }
    else if(used){
        if(accepted){
            cout<<"  Status:\t\tPDA has completed an operation on an input string\n";           
            cout<<"  Input string:\t"<<visible(original_input_string)<<endl;
            cout<<"  Input string was:\tAccepted\n";
            cout<<"  Transitions:\t"<<number_of_transitions<<endl;
            cout<<"  Crashes:\t"<<number_of_crashes<<endl;
            cout<<"  Number of transitions in accepted path: "<<accepted_path.size()<<endl;
        }
        else if(rejected){
            cout<<"  Status:\tPDA has completed an operation on an input string\n";           
            cout<<"  Input string:\t"<<visible(original_input_string)<<endl;
            cout<<"  Input string was:\tRejected\n";
            cout<<"  Transitions:\t"<<number_of_transitions<<endl;
            cout<<"  Crashes:\t"<<number_of_crashes<<endl;   
        }
        else{
            cout<<"  Status:\tPDA was operation quit by users\n";           
            cout<<"  Input string:\t"<<visible(original_input_string)<<endl;
            cout<<"  Input string was:\tnot rejected or accepted\n";
            cout<<"  Transitions:\t"<<number_of_transitions<<endl;
            cout<<"  Crashes:\t"<<number_of_crashes<<endl;

        }
    }
    else{
        cout << "  Status:\tPDA has not been run on an input string\n";       
    }

    cout << "  ================\n";
    cout << "  Course:\tCPTS 422" << endl;
    cout << "  Semester:\tFall" << endl;
    cout << "  Year:\t\t2017" << endl;
    cout << "  Instructor:\tCorrigan" << endl;
    cout << "  Team:\t\twhile(1)" << endl;
    cout << "  Team Members:\tLeigh VanCleef, Rob Pierini, KJ Dorow, Efren Alvarez" << endl;
    cout << "  Version:\t1.0" << endl;
    cout << "  ================\n";

    cout << "  Configuration Settings:" << endl;
    cout << "    Characters Before Truncation: " << configuration_settings->get_maximum_characters() << endl;
    cout << "    Maximum Transitions: " << configuration_settings->get_maximum_transitions() << endl;
    cout << "    Display Complete Paths: " << configuration_settings->complete_paths_string() << endl;
}

void Pushdown_Automaton::view_command()//calls view commands from other calls and prints Intitilall state and start character
{

    cout<<pda_description<<endl;
    states.view();
    input_alphabet.view();
    stack_alphabet.view();
    transition_function.view();
    cout<<"Initial State   = "<<initial_state<<endl;
    cout<<"Start Character = "<<start_character<<endl;
    final_states.view();
}
    
void Pushdown_Automaton::list_command()//prints string list
{
    if(string_list.size()==0){
        cout<<"List is empty!\n";
    }
    else{

        for(int index=0;index<string_list.size();index++)
            {
                cout<<index+1<<".\t"<<visible(string_list[index])<<endl;
            }
    }        
}

void Pushdown_Automaton::insert_command()//takes user input validates it and insert valid input strings into string list
{
    cout<<"Input String: ";
    string load="";
    getline(cin,load);
    bool flag=true;
    if(load!="")
    {
        if(load=="\\")
        {
            for(int index=0;index<string_list.size();index++)
                {
                    if(string_list[index]==load)
                    {
                        cout<<"That string already exists\n";
                        flag=false;
                    }
                }
                if(flag==true)
                    string_list.push_back("\\");
        }
        else
        {
            for(int index=0;index<string_list.size();index++)
                {
                    if(string_list[index]==load)
                    {
                        cout<<"That string already exists\n";
                        flag=false;
                    }
                }
               
            for(int index=0;index<load.length();index++)
            {
                if(is_valid_input_string(load)==false)
                {
                    cout<<"Invalid input string\n";
                    flag=false;
                    break;
                }
            }
            if(flag==true)
            {
                changed= true;
                cout<<"List updated\n";
                string_list.push_back(load);
            }
        }
    }
}

void Pushdown_Automaton::delete_command()//takes user input validates it and deletes input strings into string list
{
    int input_num;
    cout<<"Input sting number: ";
    string load="";
   
    getline(cin,load);
    if(istringstream ( load ) >> input_num)
    {
    
        if(input_num<1 or input_num>string_list.size())
            {
                cout<<"Index out of range\n";
            }
            else
            {
                changed =true;
                cout<<"Deleting input string: "<<string_list[input_num-1]<<endl;
                string_list.erase( string_list.begin() + input_num-1 );
            }
    }
    else
    {
        if(load!="")
        {
            cout<<"Invalid Input\n";
        }
    }
}
void Pushdown_Automaton::quit_command(){//performs actions of the quit command
    if(running){
        cout<<original_input_string<<" not accepted or rejected in "<<number_of_transitions<<" Transition(s).\n";
        cout<<"There were "<<number_of_crashes<< " crashes\n";
        running=false;
    }
}
void Pushdown_Automaton::close_command(){//writes string list file if changed, print success or failure
    
    if(changed)
        {
            ofstream str_file;
            string pda_file = name + ".str";

            str_file.open(pda_file.c_str(), ios::out | ios::trunc);

            if(!str_file.is_open())
            {
                cout << "Error writing to Configurations Settings file." << endl;
            }
            else
            {
                for(int index=0;index<string_list.size();index++){
                    str_file<<string_list[index]<<endl;
                }
                str_file.close();

                cout << "String file successfuly updated." << endl;
            }
        }
        cout<<"Closing PDA\n";
}        
bool canonical(string one, string two){//helper function for sorting, determines which string is larger
    if(one=="\\"){
        return true;
    }
    else if(two=="\\"){
        return false;
    }
    if(one.length()<two.length()){
        return true;
    }
    else if(one.length()==two.length()){
        return(one<two);
    }
    return false;
}

void Pushdown_Automaton::sort_command()//Sorts input strings if needed
{
    vector<string> temp(string_list);
    sort(string_list.begin(),string_list.end(),canonical);
    if(string_list==temp)
        cout<<"list is already sorted\n"; 
    else if(string_list.size()==0){
        cout<<"Input string list is empty\n";
    }
    else{
        changed=true;
        cout<<"List has been sorted\n";
    }

}

string Pushdown_Automaton::visible(string value){//helper function provided by prfessor, handles empty character
    const string lambda("\\");
    if(value.empty())
        value=lambda;
    return value;
}
string Pushdown_Automaton::truncate(string value){//helper function provided by prfessor, handles truncating
    if(value.length()> configuration_settings->get_maximum_characters())
        value=value.substr(0,configuration_settings->get_maximum_characters())+">";
    return value;
}

