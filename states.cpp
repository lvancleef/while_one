#include "states.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include <ctype.h>
#include "uppercase.h"


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
    string value;
    string_vector.clear();

	do{
        /* Read definition file and store everything in the file until it reaches the next keyword INPUT ALPHABET*/
        if ((definition >> value) and (To_Upper(value) != "INPUT_ALPHABET:"))
		{
		    // Check for invalid characters
			for (int i = 0; i < value.size(); i++)
			{
				if ((value[i] == '\\') or
					(value[i] == '[') or
					(value[i] == ']') or
					(value[i] == '<') or
					(value[i] == '>') or
					(value[i] <= '!') or
					(value[i] >= '~'))
				{
					valid = false;
					cout << "character '" << value << "' within state is invalid" << endl;
				}
			}

			for(int index=0;index<string_vector.size();index++)
                {
                    if(string_vector[index]==value)
                    {
                        cout<<"Error: Duplicate state\n";
                        valid=false;
                    }
                }
				string_vector.push_back(value);
		}
        // If we reach INPUT_ALPHABET, we exit the loop
		else if (To_Upper(value) == "INPUT_ALPHABET:")
			break;

	} while (!definition.eof());

	/* Check that the next keyword INPUT_ALPHABET exists */
	if (definition.eof())
	{
		cout << "Missing keyword 'INPUT_ALPHABET:' after states" << endl;
		valid = false;
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
        if(value.compare(string_vector.at(i)) == 0){
            return true;
        }
    }
    return false;
}
