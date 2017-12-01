/*
 * file: configuration_settings.cpp
 * author: lvancleef
 * version: 0.4
 * date: 11/30/2017
 *
 * notes: load and exit_command need to be finished
 */

#include "configuration_settings.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>

using namespace std;

Configuration_Settings::Configuration_Settings(string name)
{	
	application_name = name;

	maximum_number_transitions = 1;
	maximum_number_characters = 32;
	complete_paths = false;
	changed = false;

	changed = load(name);
}

bool Configuration_Settings::load(string name)
{
	application_name = name;
	string pda_file = name + ".cfg";
	
	ifstream config_file;

	config_file.open(pda_file.c_str());

	if(!config_file.is_open())
	{
		return false;
	}

	string keyword;
	// attempt to read in keywords

	while (config_file >> keyword)
	{
		if (To_Upper(keyword) == "MAXIMUM_TRANSITIONS" ||
			To_Upper(keyword) == "MAXIMUM_CHARACTERS" ||
			To_Upper(keyword) == "COMPLETE_PATHS")
		{
			// check for "="
			// check for value
			// validate value
			// check if value is different from default
			// assign value to appropriate value
			// changed = true
		}
	}

		// if even one gets loaded in (and is different from default)
			// changed = true
			// return true

	// if none get loaded in
		// return false

	return false;
}

int Configuration_Settings::get_maximum_transitions() const
{
	return maximum_number_transitions;
}

int Configuration_Settings::get_maximum_characters() const
{
	return maximum_number_characters;
}

bool Configuration_Settings::get_complete_paths() const
{
	return complete_paths;
}

string Configuration_Settings::complete_paths_string() const
{
	if (complete_paths)
		return "YES";
	else
		return "NO";
}

void Configuration_Settings::set_command()
{
	string value;
	int result;

	cout << "Maximum Transitions[" << maximum_number_transitions << "]: ";
	cin.ignore();

	if (getline(cin, value) and value.empty())
		return;

	stringstream convert(value);

	if ( !(convert >> result) )
   		result = 0;

   	if ((result > 0))
   	{
   		cout << "Maximum transitions changed from " << maximum_number_transitions << " to " << result << "." << endl;
   		maximum_number_transitions = result;

   		changed = true;
   	}
   	else
   	{
   		cout << "Input '" << value << "' entered is not a positive integer." << endl;
   	}

   	return;
}

void Configuration_Settings::truncate_command()
{
	string value;
	int result;

	cout << "Maximum Characters Before Truncation[" << maximum_number_characters << "]: ";

	cin.ignore();

	if (getline(cin, value) and value.empty())
		return;

	stringstream convert(value);

	if ( !(convert >> result) )
   		result = 0;

   	if ((result > 0))
   	{
   		cout << "Maximum characters changed from " << maximum_number_characters << " to " << result << "." << endl;
   		maximum_number_characters = result;

   		changed = true;
   	}
   	else
   	{
   		cout << "Input '" << value << "' entered is not a positive integer." << endl;
   	}

   	return;
}

void Configuration_Settings::display_command()
{
	if(complete_paths)
	{
   		cout << "Complete Paths is now FALSE." << endl;
   		complete_paths = false;
   	}
   	else
   	{
   		cout << "Complete Paths is now TRUE." << endl;
   		complete_paths = true;
   	}

   	changed = true;

	return;
}

void Configuration_Settings::exit_command()
{
	if(changed)
	{
		// open file, write config settings

		// print success or failure
	}

	exit(0);
}

