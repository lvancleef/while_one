all: main
	
uppercase:
	g++ -c uppercase.cpp	

destination:
	g++ -c destination.cpp
		
configuration_settings: 
	g++ -c configuration_settings.cpp

pushdown_automaton: input_alphabet stack_alphabet transition_function states final_states
	g++ -c pushdown_automaton.cpp 

input_alphabet:  
	g++ -c input_alphabet.cpp

stack_alphabet:  
	g++ -c stack_alphabet.cpp

transition:  
	g++ -c transition.cpp

transition_function: transition
	g++ -c transition_function.cpp

states:  
	g++ -c states.cpp

final_states:  
	g++ -c final_states.cpp

instantaneous_description:
	g++ -c instantaneous_description.cpp

main.o:  
	g++ -c main.cpp

utility.o:
	g++ -c utility.cpp

main: utility.o main.o uppercase destination configuration_settings pushdown_automaton input_alphabet stack_alphabet transition transition_function states final_states instantaneous_description
	g++  main.o uppercase.o destination.o configuration_settings.o pushdown_automaton.o input_alphabet.o stack_alphabet.o transition.o transition_function.o states.o final_states.o instantaneous_description.o -o pda

clean:
	rm  main.o uppercase.o destination.o configuration_settings.o pushdown_automaton.o input_alphabet.o stack_alphabet.o transition.o transition_function.o states.o final_states.o instantaneous_description.o pda
