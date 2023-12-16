#ifndef CARD_SET_H
#define CARD_SET_H

#include <string>
#include <vector>
#include <algorithm>
#include <random>
using std::string;
using std::vector;

#include "Card.h"
#include "Art.h"

class CardSet
{
public:

	/***** Manager Functions *****/

	// Default constructor
	CardSet();
	// Destructor
	~CardSet();

	/***** Members Functions *****/
	
	// Draws Cards from the other CardSet to this CardSet
	void draw(CardSet& other_set, int num_cards = 1, bool side = false);
	// Deals Cards from this CardSet to the other CardSet
	void deal(CardSet& other_set, int num_cards = 1, bool side = false);
	// Discards this CardSet into the other CardSet
	void discard(CardSet& other_set);
	// Collects the other CardSet into this CardSet
	void collect(CardSet& other_set);
	// Shuffles this CardSet
	void shuffle();
	// Sorts this CardSet first by suits and then by rank
	void sort_by_suit();
	// Sorts this CardSet first by rank and then by suit
	void sort_by_rank();
	// Returns number of Cards in this CardSet
	int count();
	// Sets all Cards in this CardSet so they are face up
	void all_up();
	// Sets all Cards in this CardSet so they are face down
	void all_down();

protected:

	/***** Data Members *****/

	// Vector holding all Cards in this CardSet
	vector<Card> m_cards;
};

#endif