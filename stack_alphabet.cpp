#include "stack_alphabet.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include <ctype.h>
#include "uppercase.h"

using namespace std;

Stack_Alphabet::Stack_Alphabet()
{
    alphabet = vector<char>();
}
/* Load reads the stack alphabet characters from PDA def file */
void Stack_Alphabet::load(ifstream& definition, bool& valid)
{
    alphabet.clear();
      string value;

	do{
        /* Read definition file and store everything in the file until it reaches the next keyword TRANSITION_FUNCTION: */
        if ((definition >> value) and (To_Upper(value) != "TRANSITION_FUNCTION:"))
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
            for(int index=0;index<alphabet.size();index++)
                {
                    if(alphabet[index]==(value.at(0)))
                    {
                        cout<<"Error: Duplicate stack alphabet character\n";
                        valid=false;
                    }
                }
            if(value.length()>1){
                cout<<"Error: Incorrect stack character\n";
                valid=false;
            }
            alphabet.push_back(value.at(0));

		}
        // If we reach INPUT_ALPHABET, we exit the loop
		else if (To_Upper(value) == "TRANSITION_FUNCTION:")
			break;

	} while (!definition.eof());

	/* Check that the next keyword INPUT_ALPHABET exists */
	if (definition.eof())
	{
		cout << "Missing keyword 'TRANSITION_FUNCTION:' after Stack Alphabet" << endl;
		valid = false;
	}

}
/*
void Stack_Alphabet::validate(vector<char> input_alphabet, bool& valid)
{
    valid = true;
    for(int i = 0; i < (int)alphabet.size(); i++)
    {
        for(int j = 0; (int)input_alphabet.size(); j++)
        {
            if(input_alphabet[j].compare(alphabet[i]) == 0)
                break;
            else
            {
                cout << "Error: Stack alphabet contains characters not defined in input alphabet!" << endl;
                valid = false;
                break;
            }
        }
    }
}
*/
void Stack_Alphabet::view()const
{
    cout << "Stack Alphabet: ";
    /* Print every character in vector */
    for(int i = 0; i < (int)alphabet.size(); i++)
        cout << alphabet.at(i) << " ";

    cout << endl;

}
bool Stack_Alphabet::is_element(char value)const
{

    for(int i = 0; i < (int)alphabet.size(); i++)
    {
        // If the value is part of the character vector, then we return true
        if(value == alphabet.at(i))
            return true;
    }
    return false;
}

