#ifndef CHIP_H
#define CHIP_H

#include <string>
#include <vector>
using std::to_string;
using std::string;
using std::vector;

#include "Art.h"

class Chip
{
public:

	/***** Manager Functions *****/

	// Default constructor
	Chip();
	// Constructor which takes argument for value of this Chip
	Chip(int value);
	// Copy constructor
	Chip(const Chip& other_chip);
	// Destructor
	~Chip();

	/***** Overloaded Operators *****/

	// Copy assignment operator
	Chip operator=(const Chip& other_chip);

	/***** Member Functions *****/

	// Adds value to this Chip
	void add(int value);
	// Subtracts value from this Chip
	void sub(int value);
	// Returns value of this Chip
	int value();
	// Returns Art of this Chip
	Art art(bool zoom = true);

private:

	/***** Data Members *****/

	// Int holding value of this Chip
	int m_value;
};

#endif