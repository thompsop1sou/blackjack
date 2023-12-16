#include "Rank.h"

/***** Manager Functions *****/

// Default constructor
Rank::Rank() : m_rank(1)
{}

// Constructor with int argument
Rank::Rank(int rank) : m_rank()
{
	if (rank > 0 && rank < 14)
		m_rank = rank;
	else
		m_rank = 1;
}

// Constructor with string argument
Rank::Rank(string rank) : m_rank()
{
	for (int i = 0; i < rank.length(); ++i)
		rank[i] = tolower(rank[i]);

	if (rank == "2" || rank == "two")
		m_rank = 2;
	else if (rank == "3" || rank == "three")
		m_rank = 3;
	else if (rank == "4" || rank == "four")
		m_rank = 4;
	else if (rank == "5" || rank == "five")
		m_rank = 5;
	else if (rank == "6" || rank == "six")
		m_rank = 6;
	else if (rank == "7" || rank == "seven")
		m_rank = 7;
	else if (rank == "8" || rank == "eight")
		m_rank = 8;
	else if (rank == "9" || rank == "nine")
		m_rank = 9;
	else if (rank == "10" || rank == "ten")
		m_rank = 10;
	else if (rank == "j" || rank == "jack")
		m_rank = 11;
	else if (rank == "q" || rank == "queen")
		m_rank = 12;
	else if (rank == "k" || rank == "king")
		m_rank = 13;
	else
		m_rank = 1;
}

// Copy constructor
Rank::Rank(const Rank& other_rank) : m_rank(other_rank.m_rank)
{}

// Destructor
Rank::~Rank()
{}

/***** Overloaded Operations *****/

// Copy assignment operator
Rank Rank::operator=(const Rank& other_rank)
{
	if (this != &other_rank)
		m_rank = other_rank.m_rank;

	return *this;
}

// Equal to comparison operator
bool Rank::operator==(const Rank& other_rank)
{
	return (m_rank == other_rank.m_rank);
}

// Greater than comparison operator
bool Rank::operator>(const Rank& other_rank)
{
	return (m_rank > other_rank.m_rank);
}

// Less than comparison operator
bool Rank::operator<(const Rank& other_rank)
{
	return (m_rank < other_rank.m_rank);
}

// Greater than or equal to comparison operator
bool Rank::operator>=(const Rank& other_rank)
{
	return  (m_rank >= other_rank.m_rank);
}

// Less than or equal to comparison operator
bool Rank::operator<=(const Rank& other_rank)
{
	return  (m_rank <= other_rank.m_rank);
}

/***** Member Functions *****/

// Returns name of this Rank
string Rank::name()
{
	string name;

	switch (m_rank)
	{
	case 1: name = "Ace"; break;
	case 2: name = "Two"; break;
	case 3: name = "Three"; break;
	case 4: name = "Four"; break;
	case 5: name = "Five"; break;
	case 6: name = "Six"; break;
	case 7: name = "Seven"; break;
	case 8: name = "Eight"; break;
	case 9: name = "Nine"; break;
	case 10: name = "Ten"; break;
	case 11: name = "Jack"; break;
	case 12: name = "Queen"; break;
	case 13: name = "King"; break;
	}

	return name;
}

// Returns abbreviation of this Rank
string Rank::abbrev()
{
	string abbrev;

	switch (m_rank)
	{
	case 1: abbrev = "A"; break;
	case 2: abbrev = "2"; break;
	case 3: abbrev = "3"; break;
	case 4: abbrev = "4"; break;
	case 5: abbrev = "5"; break;
	case 6: abbrev = "6"; break;
	case 7: abbrev = "7"; break;
	case 8: abbrev = "8"; break;
	case 9: abbrev = "9"; break;
	case 10: abbrev = "10"; break;
	case 11: abbrev = "J"; break;
	case 12: abbrev = "Q"; break;
	case 13: abbrev = "K"; break;
	}

	return abbrev;
}