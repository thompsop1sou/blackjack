#ifndef DECK_H
#define DECK_H

#include "CardSet.h"

class Deck : public CardSet
{
public:

	/***** Manager Functions *****/

	// Default constructor that creates one 52-card deck
	Deck();
	// Constructor with argument for number of 52-card decks
	Deck(int num_decks);

	/***** Member Functions *****/

	// Returns Art of this Deck
	Art art(bool zoom = true);
};

#endif