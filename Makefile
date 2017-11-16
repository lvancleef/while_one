all: main

pushdown_automaton: input_alphabet stack_alphabet transition_function states final_states
	g++ -c Pushdown_Automaton.cpp 

input_alphabet:  
	g++ -c Input_Alphabet.cpp

stack_alphabet:  
	g++ -c Stack_Alphabet.cpp

transition_function: transition
	g++ -c Transition_Function.cpp

states:  
	g++ -c States.cpp

final_states:  
	g++ -c Final_States.cpp

instantaneous_description:
	g++ -c Instantaneous_Description.cpp
	
transition:  
	g++ -c Transition.cpp

main.o:  
	g++ -c main.cpp

main: main.o pushdown_automaton transitions final_statess transition_function tape_alphabet stack_alphabet input_alphabet states
	g++  .o Stack_Alphabet.o Input_Alphabet.o main.o Transition.o Transition_Function.o Tape.o States.o Final_States. Pushdown_Automaton.o -o pda

clean:
	rm  .o Instantaneous_Description.o Input_Alphabet.o Stack_Alphabet.o Transition_Function.o States.o Final_States.o Pushdown_Automaton.o Transition.o crash.o main.o tm