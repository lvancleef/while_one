/*
 * file: main.cpp
 * author: lvancleef
 * version: 0.2
 * date: 11/30/2017
 */

#include "configuration_settings.h"
#include "pushdown_automaton.h"
#include "input_alphabet.h"
#include "stack_alphabet.h"
#include "transition.h"
#include "transition_function.h"
#include "states.h"
#include "final_states.h"
#include "instantaneous_description.h"
#include "uppercase.h"

#include <iostream>
#include <sstream>
#include <stdlib.h>

#include <string>

void help_command()
{
	cout<<"[C]lose\t\tClose pushdown automaton\n";
    cout<<"[D]elete\tDelete input string from list\n";
    cout<<"Dis[p]lay\tComplete paths through pushdown automaton\n";
    cout<<"E[x]it\t\tExit application\n";
    cout<<"[H]elp\t\tHelp User\n";
    cout<<"[I]nsert\tInsert input string into list\n";
    cout<<"[L]ist\t\tDisplay list of input strings\n";
    cout<<"[O]pen\t\tOpen pushdown automaton\n";
    cout<<"[Q]uit\t\tQuit operation of PDA on input string\n"; 
    cout<<"[R]un\t\tRun PDA on input string\n";
    cout<<"S[e]t\t\tSet maximum number of transitions\n";
    cout<<"Sho[w]\t\tShow status of application\n";
    cout<<"[S]ort\t\tSort input strings in canonical order\n";
    cout<<"[T]runcate\tTruncate instantaneous description\n";
    cout<<"[V]iew\t\tView pushdown automaton\n";

    return;
}

void show_command(Configuration_Settings * configuration_settings)
{
	cout << "  Course:\tCPTS 422" << endl;
	cout <<	"  Semester:\tFall" << endl;
	cout <<	"  Year:\t\t2017" << endl;
	cout <<	"  Instructor:\tCorrigan" << endl;
	cout <<	"  Team:\twhile(1)" << endl;
	cout <<	"  Team Members:\tLeigh VanCleef, Rob Pierini, KJ Dorow, Efren Alvarez" << endl;
	cout <<	"  Version:\t1.0" << endl;

	cout <<	"\n  Configuration Settings:" << endl;
	cout <<	"\tCharacters Before Truncation: " << configuration_settings->get_maximum_characters() << endl;
	cout <<	"\tMaximum Transitions: " << configuration_settings->get_maximum_transitions() << endl;
	cout <<	"\tDisplay Complete Paths: " << configuration_settings->complete_paths_string() << endl;

	cout << "\n  No PDA is currently open\n" << endl;

	return;
}

void open_command(Pushdown_Automaton & pushdown_automaton,
			 Configuration_Settings & configuration_settings,
			 bool init = false, string name = "")
{
	string filename = name;
	bool open = false;
	bool initiailized = init;

	do
	{
		if (!initiailized)
		{
			cout << "PDA name: ";
			cin >> filename;
			if (filename.empty())
				return;
		}

		pushdown_automaton.load(filename);

		open = pushdown_automaton.pda_main();

		initiailized = false;
		filename = "";

	} while(open);

	return;
}

int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		cout << "PDA takes at most one argument. Exiting." << endl;
		return 0;
	}

	Configuration_Settings configuration_settings(argv[0]);
	Pushdown_Automaton pushdown_automaton(&configuration_settings);

	if (argc == 2)
	{
		open_command(pushdown_automaton, configuration_settings,
					 true, argv[1]);
	}

	string choice;
	int count = 0;

	do
	{
		cout << "Command: ";
		cin >> choice;

		if (To_Upper(choice) == "H")
		{
			count = 0;
			help_command();
		}
		else if(To_Upper(choice) == "W")
		{
			count = 0;
			show_command(&configuration_settings);
		}
		else if(To_Upper(choice) == "O")
		{
			count = 0;
			open_command(pushdown_automaton, configuration_settings);
		}
		else if (To_Upper(choice) == "E")
		{
			count = 0;
			configuration_settings.set_command();
		}
		else if (To_Upper(choice) == "T")
		{
			count = 0;
			configuration_settings.truncate_command();
		}
		else if (To_Upper(choice) == "P")
		{
			count = 0;
			configuration_settings.display_command();
		}
		else if (To_Upper(choice) == "X")
		{
			count = 0;
			configuration_settings.exit_command();
		}
		else if(To_Upper(choice) == "C"
				|| To_Upper(choice) == "D"
				|| To_Upper(choice) == "I"
				|| To_Upper(choice) == "L"
				|| To_Upper(choice) == "Q"
				|| To_Upper(choice) == "R"
				|| To_Upper(choice) == "S"
				|| To_Upper(choice) == "V")
		{
			count = 0;
			cout << "No PDA is currently open." << endl;
		}
		else
		{
			count++;
			if (count == 5)
			{	
				cout << "Too many invalid selections. Exiting." << endl;
				configuration_settings.exit_command();
			}
			else
				cout << "Please enter a valid character. 'H' provides a list." << endl;
		}

	} while (1);

	return 0;
}