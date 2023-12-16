#ifndef RANK_H
#define RANK_H

#include <string>
using std::string;

#include "Art.h"

class Rank
{
public:

	/***** Manager Functions *****/

	// Default constructor
	Rank();
	// Constructor with int argument
	Rank(int rank);
	// Constructor with string argument
	Rank(string rank);
	// Copy constructor
	Rank(const Rank& other_rank);
	// Destructor
	~Rank();

	/***** Overloaded Operations *****/

	// Copy assignment operator
	Rank operator=(const Rank& other_rank);
	// Equal to comparison operator
	bool operator==(const Rank& other_rank);
	// Greater than comparison operator
	bool operator>(const Rank& other_rank);
	// Less than comparison operator
	bool operator<(const Rank& other_rank);
	// Greater than or equal to comparison operator
	bool operator>=(const Rank& other_rank);
	// Less than or equal to comparison operator
	bool operator<=(const Rank& other_rank);

	/***** Member Functions *****/

	// Returns name of this Rank
	string name();
	// Returns abbreviation of this Rank
	string abbrev();

private:

	/***** Data Member *****/

	// Int holding rank value (from 1 to 13)
	int m_rank;
};

#endif