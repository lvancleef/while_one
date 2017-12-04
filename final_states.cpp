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
    string value;

	do
	{
        // Read definition file
        if ((definition >> value)
            and (To_Upper(value) == "FINAL_STATES:")
            and (definition >> value))
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
					cout << "Error: Illegal character '" << value.at(i) << "' within keyword 'FINAL_STATES:' is invalid" << endl;
                    			break;
				}
			}
			final_names.push_back(value);
		}

	} while (!definition.eof());
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
