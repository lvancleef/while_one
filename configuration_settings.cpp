/*
 * file: configuration_settings.cpp
 * author: lvancleef
 * version: 0.1
 * date: 11/26/2017
 *
 * notes: this is mostly just the skeleton. 
 * 		  work still needs to be done.
 */

#include "configuration_settings.h"
#include <string>

using namespace std;

Configuration_Settings::Configuration_Settings(string name)
{	
	application_name = name;

	// if we're loading in the constructor, this needs to be edited
	maximum_number_transitions = 1;
	maximum_number_characters = 32;
	complete_paths = false;
	changed = false;
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

void Configuration_Settings::set_command()
{
	// needs content
	return;
}

void Configuration_Settings::truncate_command()
{
	// needs content
	return;
}

void Configuration_Settings::display_command()
{
	// needs content
	return;
}

