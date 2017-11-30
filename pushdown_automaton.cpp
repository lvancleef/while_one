#include "pushdown_automaton.h"
#include "input_alphabet.h"
#include "stack_alphabet.h"
#include "transition_function.h"
#include "states.h"
#include "final_states.h"
#include "instantaneous_description.h"
#include "configuration_settings.h"
#include "uppercase.h"

#include <string>
#include <iostream>

using namespace std;

// Pushdown_Automaton::Pushdown_Automaton()
// {
// }

bool Pushdown_Automaton::is_accepted(Instantaneous_Description instantaneous_description)
{
    
}

void Pushdown_Automaton::load(string definition_file_name)
{
    string Def_File=name;
    Def_File+=".def";
    ifstream definition;
    definition.open(Def_File.c_str());
    
    pda_description="";
    valid=true;
    used=false;
    running=false;
    accepted=false;
    rejected=false;
    string keyword;
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
        else
        {
            Valid=false;
        cout<<"States is missing\n";
        Valid=false;
        }
    }
    states.load(definition, valid);
    input_alphabet.load(definition, valid);
    stack_alphabet.load(definition, valid);
    transition_function.load(definition, valid);
    
    definition>>keyword= initial_state;

    if((To_Upper(definition>>keyword)!="START_CHARACTER:"))
    {
        cout<<"START_CHARACTER is missing\n";
        valid=false;
    }
    else{
        definition>>keyword;
        if(keyword.length()==1){
            keyword[0]=START_CHARACTER;
        }
    }

    if((To_Upper(definition>>keyword)!="FINAL_STATES:"))
    {
        cout<<"FINAL_STATES is missing\n";
        valid=false;
    }
    final_states.load(definition, valid);
}

bool Pushdown_Automaton::pda_main(Configuration_Settings configuration_settings)
{//check if valid is false print error
    return true;
}

string Pushdown_Automaton::perform_transition(Instantaneous_Description instantaneous_description, int &number_of_transitions_performed)
{
    
    
    return "rejected";
}

string Pushdown_Automaton::commands()
{
    int exit;
    string Command ="";
//command loop
    do{
        cout<<"Command: ";
        cin>>Command;   
        
            if (Command == "c" || Command == "C"){
                return "close";
            }   
            else if(Command == "d"||Command== "D"){
                delete_command();
            }
            else if(Command == "p"||Command == "P"){               
            }   
            else if(Command == "x"||Command== "X"){
                exit=1;
            }      
            else if(Command == "H" || Command== "h"){   
                help_command();
            }
            else if(Command == "I" || Command== "i"){
                insert_command();
            }              
            else if(Command == "L" || Command== "l"){
                list_command();
            }
            else if(Command=="Q"||Command=="q"){
                return "quit";
            }
            else if(Command=="o"||Command=="O"){
                return "open";
            }                
            else if(Command == "R" ||Command== "r"){
                return "run";
            }               
            else if(Command == "e" || Command== "E"){
                 configuration_settings.set_command();
            }               
            else if(Command == "W" || Command== "w"){
                show_command();
            }
            else if(Command == "S"|| Command == "s"){
                sort_command();
            }   
            else if(Command == "T" || Command == "t"){               
                 configuration_settings.truncate_command();
            }               
            else if(Command == "V" || Command == "v"){
                view_command();
            }
            else{
                cout<<"INVALID Commmand\n";
            }           
    cout<<endl;
    }while (exit!=1);
    return "exit";
}
    
bool Pushdown_Automaton::is_valid_input_string(string value)
{
    return true;
}

void Pushdown_Automaton::print_id(Instantaneous_Description instantaneous_description)
{
    cout<<"["<<number_of_transitions<<"]. ["<<instantaneous_description.get_current_level()<<"] (";
    cout<<instantaneous_description.get_current_state()<<",";
    cout<<truncate(visible(instantaneous_description.get_remaining_input_string()))<<", ";
    cout<<truncate(visible(instantaneous_description.get_stack()))<<")\n";
}

void Pushdown_Automaton::initialize_string_list()
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
                if(load=="\\")
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
                                                       
                        for(int index;index<load.length();index++)
                        {
                            if(is_valid_input_string(load)==false)
                            {
                                cout<<"Invalid input string\n";
                                flag=false;
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
    
void Pushdown_Automaton::help_command()
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

void Pushdown_Automaton::show_command()
{
    cout<<"show command\n";//show app data
}

void Pushdown_Automaton::view_command()
{
    cout<<"view command\n";//the pda loaded
}
    
void Pushdown_Automaton::list_command()
{
    for(int index=0;index<string_list.size();index++)
        {
            cout<<index+1<<". "<<string_list[index]<<endl;
        }
}

void Pushdown_Automaton::insert_command()
{
    cout<<"Input String: ";
    string load="";
    cin.ignore();
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
                    string_list.push_back(load);
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
            for(int index;index<load.length();index++)
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
                cout<<"List updated\n";
                string_list.push_back(load);
            }
        }
    }
}

void Pushdown_Automaton::delete_command()
{
    int input_num;
    cout<<"Input sting number: ";
    string load="";
    cin.ignore();
    getline(cin,load);
    if(istringstream ( load ) >> input_num)
    {
        if(input_num<1 or input_num>string_list.size())
            {
                cout<<"Index out of range\n";
            }
            else
            {
                cout<<"Deleting index "<<input_num<<endl;
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

void Pushdown_Automaton::sort_command()
{
    cout<<"sort command\n";
}
string Pushdown_Automaton::visible(string value){
    const string lambda("//");
    if(value.empty())
        value=lambda;
    return value;
}
string Pushdown_Automaton::truncate(string value){
    if(value.length()> configuration_settings.get_maximum_characters())
        value=value.substr(0,configuration_settings.get_maximum_characters())+">";
    return value;
}

