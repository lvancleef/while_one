#ifndef STATES_H_
#define STATES_H_

#include <string>
#include <vector>
#include <fstream>

using namespace std;

class States
{
private:
    vector<string> string_vector;

public:
    States();
    void load(ifstream& definition, bool& valid);
    void view()const;
    bool is_element(string value)const;

};
#endif // STATES_H_
