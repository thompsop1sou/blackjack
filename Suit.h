#ifndef SUIT_H
#define SUIT_H

#include <string>
using std::string;

#include "Art.h"

class Suit
{
public:

	/***** Manager Functions *****/

	// Default constructor
	Suit();
	// Constructor with int argument
	Suit(int suit);
	// Constructor with string argument
	Suit(string suit);
	// Copy constructor
	Suit(const Suit& other_suit);
	// Destructor
	~Suit();

	/***** Overloaded Operations *****/

	// Copy assignment operator
	Suit operator=(const Suit& other_suit);
	// Equal to comparison operator
	bool operator==(const Suit& other_suit);
	// Greater than comparison operator
	bool operator>(const Suit& other_suit);
	// Less than comparison operator
	bool operator<(const Suit& other_suit);
	// Greater than or equal to comparison operator
	bool operator>=(const Suit& other_suit);
	// Less than or equal to comparison operator
	bool operator<=(const Suit& other_suit);

	/***** Member Functions *****/

	// Returns name of this Suit
	string name();
	// Returns abbreviation of this Suit
	string abbrev();
	// Returns small symbol of this Suit
	string small_symbol();
	// Returns large symbol of this Suit
	Art large_symbol();

private:

	/***** Data Member *****/

	// Int holding suit value (from 0 to 3)
	int m_suit;
};

#endif