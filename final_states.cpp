#include "final_states.h"
#include "states.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

Final_States::Final_States()
{
    States();
    final_names = vector<string>();
}
void Final_States::load(ifstream& definition, bool& valid)
{
    string get_states;

    getline(definition, get_states); // Store contents of definition in get_states

    /* We need to allocate a character pointer 'c' to hold contents of
        FINAL_STATES. */
    char* c = new char[get_states.length() + 1];
    strcpy(c, get_states.c_str()); // Now we 'transfer' States to c

    // Here is where we check if 'FINAL_STATES:' keyword exists
    if(get_states.substr(0, 13).compare("FINAL_STATES:") != 0) // comparing length of get_states to "FINAL_STATES:"
    {
        cout << "Error: Keyword 'FINAL_STATES:' doesn't exist!" << endl;
        valid = false;
        return;
    }

    // Separate each state from 'FINAL_STATES' by using strtok. strtok splits string into tokens strtok (string to truncate, delimeters)
    char* separate_states = strtok(c, " "); // Created separate_states to store each state separately instead of having the string
    separate_states = strtok(NULL, " ");

    while(separate_states != NULL)
    {
        string s(separate_states); //creating string s to store each token
        final_names.push_back(s);
        separate_states = strtok(NULL, " ");
    }

    delete[] c;
    delete[] separate_states;

    /* Check for duplicates by comparing each reference of the elements in the vector  */
    for(int i = 0; i < (int)final_names.size(); i++)
    {
        string name = final_names.at(i);
        int j = 0; // We now compare if each element in the vector is printable by using isprint()

        while(isprint(name[j]))
            j++;

        if(j != (int)name.length())
        {
            cout << "Error: The final states are not printable characters" << endl;
            valid = false;
            return;

        }
        for(int k = i + 1; k < (int)final_names.size(); k++)
        {
            if(final_names.at(i).compare(final_names.at(k)) == 0) // If an element matches with another element, then return false
            {
                cout << "Error: States in final states are not unique!" << endl;
                valid = false;
                return;
            }
        }
    }
}
/* Determine if the list of final states are states that exist in the states vector
    from the states class. */
void Final_States::validate(vector<string> string_vector, bool& valid)
{
    valid = true;
    for(int i = 0; i < (int)string_vector.size(); i++)
    {
        for(int j = 0; (int)final_names.size(); j++)
        {
            /* If the contents of final_names vector matches the
                contents of states vector, then final states exist within
                States vector */
            if(final_names[j].compare(string_vector[i]) == 0)
                break;
            else
            {
                cout << "Error: List of states don't contain a final state!" << endl;
                valid = false;
                break;
            }
        }
    }
}
void Final_States::view() const
{
    cout << "Final states: ";
    for(int i = 0; i < (int)final_names.size(); i++)
        cout << final_names.at(i) << " ";

    cout << endl;
}
bool Final_States::is_element(string value) const
{
    for(int i = 0; i < (int)final_names.size(); i++)
    {
        if(value.compare(final_names.at(i)) == 0)
            return true;
    }
    return false;
}
