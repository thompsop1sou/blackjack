#ifndef HAND_H
#define HAND_H

#include <string>
using std::string;

#include "CardSet.h"

class Hand : public CardSet
{
public:

	/***** Manager Functions *****/

	// Default constructor
	Hand();
	// Destructor
	~Hand();

	/***** Member Functions *****/

	// Returns blackjack score of this Hand
	int score();
	// Returns true if this Hand can be split (per Blackjack rules)
	bool splittable();
	// Returns Art of this Hand
	Art art(bool zoom = true);

private:

	/***** Data Members *****/

	// Bool determining whether cards display as expanded or condensed
	bool m_spread;
};

#endif