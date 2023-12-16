#ifndef CARD_H
#define CARD_H

#include "Art.h"
#include "Rank.h"
#include "Suit.h"

class Card
{
public:

	/***** Static Members *****/

	// Static function to compare two Cards by suit first and then by rank
	static int compare_by_suit(Card card1, Card card2);
	// Static function to compare two Cards by rank first and then by suit
	static int compare_by_rank(Card card1, Card card2);

	/***** Manager Functions *****/

	// Default constructor
	Card();
	// Constructor with int arguments for Rank and Suit
	Card(int rank, int suit, bool side = true);
	// Constructor with string arguments for Rank and Suit
	Card(string rank, string suit, bool side = true);
	// Copy constructor
	Card(const Card& other_card);
	// Destructor
	~Card();

	/***** Overloaded Operations *****/

	// Copy assignment operator
	Card operator=(const Card& other_card);
	// Equality comparison operator
	bool operator==(const Card& other_card);

	/***** Member Functions *****/

	// Returns suit of this Card
	Suit suit();
	// Returns rank of this Card
	Rank rank();
	// Returns name of this Card
	string name();
	// Returns abbreviation of this Card
	string abbrev();
	// Flips this Card face up
	void up();
	// Flips this Card face down
	void down();
	// Returns Art of this Card
	Art art(bool zoom = true);

private:

	/***** Data Members *****/

	// Rank of this Card
	Rank m_rank;
	// Suit of this Card
	Suit m_suit;
	// Bool determining whether this card appears face-up (true) or face-down (false)
	bool m_side;
};

#endif