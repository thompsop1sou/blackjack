#ifndef DEALER_H
#define DEALER_H

#include "Deck.h"
#include "Hand.h"
#include "Art.h"

class Dealer
{
public:

	/***** Manager Functions *****/

	// Default constructor
	Dealer();
	// Constructor with argument for number of decks in shoe
	Dealer(int num_decks);
	// Destructor
	~Dealer();

	/***** Members Functions *****/

	// Returns the Deck m_shoe of this Dealer by reference
	Deck& shoe();
	// Returns the Deck m_discard of this Dealer by reference
	Deck& discard();
	// Returns the Hand m_hand of this Dealer by reference
	Hand& hand();
	// Returns title of this Dealer
	Art title(bool zoom = true);
	// Returns Art of this Dealer
	Art art(bool zoom = true);

private:

	/***** Data Members *****/

	// "Shoe" (i.e. deck) to deal Cards from
	Deck m_shoe;
	// Discard pile to send used Cards to
	Deck m_discard;
	// Current hand of this Dealer
	Hand m_hand;
};

#endif