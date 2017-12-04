#ifndef STACK_ALPHABET_H
#define STACK_ALPHABET_H

#include <string>
#include <vector>
#include <fstream>
#include "uppercase.h"

using namespace std;

class Stack_Alphabet
{
private:
    vector<char> alphabet;

public:
    Stack_Alphabet();
    void load(ifstream& definition, bool& valid);
//    void validate(vector<char> input_alphabet, bool& valid);
    void view()const;
    bool is_element(char value)const;

};
#endif // STACK_ALPHABET_H
