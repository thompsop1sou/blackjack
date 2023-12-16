#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <functional>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::chrono::seconds;
using std::function;

#include "../components/Art.h"

class Input
{
public:

	// Enum type for the kind of this input
	enum Kind { None, Choice, Number };

	/***** Manager Functions *****/

	// Default constructor
	Input();
	// Destructor
	~Input();

	/***** Member Functions *****/

	// Returns value of this Input
	int value();
	// Sets kind of this Input
	void set_kind(Kind kind);
	// Sets Choices of this Input
	void set_choices(vector<string> choices);
	// Sets prompt of this Input
	void set_prompt(string prompt);
	// Sets condition of this Input
	void set_condition(function<bool(string)> condition);
	// Sets delay of this Input
	void set_delay(int delay);
	// Gets input value from user
	void retrieve();
	// Returns title of this Input
	Art title(bool zoom = true);
	// Returns Art of this Input
	Art art(bool zoom = true);

private:

	/***** Member Functions *****/

	// Find index of elem in vect, returns -1 if not found
	int find(string elem, vector<string> vect, bool case_sens = false);
	// Converts a string to lowercase
	string to_lower(string str);

	/***** Data Members *****/

	// Kind of input (Choose, Enter, or Show)
	Kind m_kind;
	// Choices for this input
	vector<string> m_choices;
	// Prompt message to display if user input is required
	string m_prompt;
	// Conditional function which must return true for input to be accepted
	function<bool(string)> m_condition;
	// Length of time to wait for None Inputs
	seconds m_delay;
	// Value of user input
	int m_value;
};

#endif