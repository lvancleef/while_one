#ifndef FINAL_STATES_H_
#define FINAL_STATES_H_

#include <string>
#include <vector>
#include <fstream>
#include "states.h"

using namespace std;

class Final_States
{
private:
    vector <string> final_names;

public:
    Final_States();
    void load(ifstream& definition, bool& valid);
    void validate(States& states, bool& valid);
    void view() const;
    bool is_element(string value) const;

};
#endif // FINAL_STATES_H_
