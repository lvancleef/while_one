/*
 * file: configuration_settings.h
 * author: lvancleef
 * version: 1.0
 * date: 11/26/2017
 */

#ifndef CONFIGURATION_SETTINGS_H_
#define CONFIGURATION_SETTINGS_H_

#include <string>

using namespace std;

class Configuration_Settings
{
private:
	string application_name;
	int maximum_number_transitions;
	int maximum_number_characters;
	bool complete_paths;
	bool changed;

public:
	Configuration_Settings(string name);
	
	int get_maximum_transitions() const;
	int get_maximum_characters() const;
	bool get_complete_paths() const;

	void set_command();
	void truncate_command();
	void display_command();

};


#endif