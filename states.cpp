#include "states.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include <ctype.h>

using namespace std;

States::States()
{
    string_vector = vector<string>();
}
/*
    Load will read in the definition file to get names of States.
        Each must be unique and should not contain reserved characters.
*/
void States::load(ifstream& definition, bool& valid)
{
    string get_states;

    getline(definition, get_states); // Store contents of definition in get_states

    /* We need to allocate a character pointer 'c' to hold contents of
        States. */
    char* c = new char[get_states.length() + 1];
    strcpy(c, get_states.c_str()); // Now we 'transfer' States to c

    // Here is where we check if 'STATES:' keyword exists
    if(get_states.substr(0, 7).compare("STATES:") != 0) // comparing length of get_states to "STATES:"
    {
        cout << "Error: Keyword 'STATES:' doesn't exist!" << endl;
        valid = false;
        return;
    }

    // Separate each state from 'STATES' by using strtok. strtok splits string into tokens strtok (string to truncate, delimeters)
    char* separate_states = strtok(c, " "); // Created separate_states to store each separate state
    separate_states = strtok(NULL, " ");

    while(separate_states != NULL)
    {
        string s(separate_states); //creating string s to store each token
        string_vector.push_back(s);
        separate_states = strtok(NULL, " ");
    }

    delete[] c;
    delete[] separate_states;

    /* Check for duplicates by comparing the reference to the elements in the vector        */
    for(int i = 0; i < (int)string_vector.size(); i++)
    {
        string name = string_vector.at(i);
        int j = 0; // We now compare if each element in the vector is printable by using isprint

        while(isprint(name[j]))
            j++;

        if(j != (int)name.length())
        {
            cout << "Error: States are not printable characters" << endl;
            valid = false;
            return;

        }
        for(int k = i + 1; k < (int)string_vector.size(); k++)
        {
            if(string_vector.at(i).compare(string_vector.at(k)) == 0)
            {
                cout << "Error: States are not unique!" << endl;
                valid = false;
                return;
            }
        }
    }
}
/* Display state names */
void States::view() const
{
    cout << "States: ";

    /* We return the number of elements in the vector
        so that they are displayed */
    for(int i = 0; i < (int)string_vector.size(); i++)
        cout << string_vector.at(i) << " ";

    cout << endl;
}
/* is_element will determine if the state names are elements of states
    from definition file. */
bool States::is_element(string value) const
{
    for(int i = 0; i < (int)string_vector.size(); i++)
    {
        if(value.compare(string_vector.at(i)) == 0)
            return true;
    }
    return false;
}
