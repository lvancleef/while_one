#include "stack_alphabet.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include <ctype.h>

using namespace std;

Stack_Alphabet::Stack_Alphabet()
{
    alphabet = vector<char>();
}
/* Load reads the stack alphabet characters from PDA def file */
void Stack_Alphabet::load(ifstream& definition, bool& valid)
{
    // Retrieve the contents of def file and load them in string stack_alpha
    string stack_alpha;
    getline(definition, stack_alpha);

    /* Check if 'STACK_ALPHABET:" keyword exists by checking the exact size of keyword
        plus the null character at the end, which is 15 characters, by the actual keyword */
    if(stack_alpha.substr(0, 15).compare("STACK_ALPHABET:") != 0)
    {
        cout << "Error: 'STACK_ALPHABET:' keyword doesn't exist!" << endl;
        valid = false;
        return;
    }
    /* We need to start looping after the "STACK_ALPHABET:/" Keyword
        which would be 16. Then we can start loading in each alphabet
        character */
        for(int i = 16; i <= (int)stack_alpha.length(); i++)
        {
            /* Check whether stack_alpha has non printable characters by using
                isprint() at every reference i in stack_alpha*/
            if(isprint(stack_alpha.at(i)) == 0)
            {
                cout << "Error: Stack alphabet has a non-printable character!" << endl;
                valid = false;
                return;
            }

            // If we pass the printable test, we load characters into the character vector
            else
            {
                i++; // We need to keep counting i, if it reaches continue in the next if loop, in order to keep iterating
                alphabet.push_back(stack_alpha.at(i));

                // Check if string has multiple characters, separated by a space
                if(stack_alpha.at(i) == ' ')
                    continue;

                else
                {
                    cout << "Error: Stack alphabet contains invalid characters" << endl;
                    valid = false;
                    return;
                }

            }

        }
}
/* Validate function for validate? REVIEW DESIGN */
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

