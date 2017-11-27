#ifndef instantaneous_description_h
#define instantaneous_description_h
#include <string>
using namespace std;
class instantaneous_description{
    private:
        string current_state;
        string remaining_input_string;
        string stack;
        int current_level;
    public:
        instantaneous_description();
        instantaneous_description(string initial_state, string input_string, char start_character, int level);
        void view(Configuration_Settings_Pointer configuration_settings_pointer) const;
        string state() const;
        char input_character() const;
        char top_of_stack() const;
        bool is_empty_stack() const;
        bool is_empty_remaining_input_string() const;
    };
#endif