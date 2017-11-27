#ifndef instantaneous_description_h
#define instantaneous_description_h
#include <string>
using namespace std;
class Instantaneous_Description{
    private:
        string current_state;
        string remaining_input_string;
        string stack;
        int current_level;
    public:
        Instantaneous_Description();
        Instantaneous_Description(string initial_state, string input_string, char start_character, int level);
        void view() const;
        string state() const;
        char input_character() const;
        char top_of_stack() const;
        bool is_empty_stack() const;
        bool is_empty_remaining_input_string() const;
    };
    typedef Instantaneous_Description *instantaneous_description;

#endif