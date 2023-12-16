#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using std::string;

#include "Hand.h"
#include "Chip.h"
#include "Art.h"

class Player
{
public:

	/***** Manager Functions *****/

	// Default constructor
	Player();
	// Destructor
	~Player();

	/***** Members Functions *****/

	// Returns the Chip m_stack of this Player by reference
	Chip& stack();
	// Returns the Chip m_bet of this Player by reference
	Chip& bet();
	// Returns the Hand m_hand of this Player by reference
	Hand& hand();
	// Returns the Chip m_split_bet of this Player by reference
	Chip& split_bet();
	// Returns the Hand m_split_hand of this Player by reference
	Hand& split_hand();
	// Returns title of this Player
	Art title(bool zoom = true);
	// Returns Art of this Player
	Art art(bool zoom = true);

private:

	/***** Data Members *****/

	// Total value of chips that this Player has in their stack
	Chip m_stack;
	// Value of current (main) bet for this Player
	Chip m_bet;
	// Current (main) hand of this Player
	Hand m_hand;
	// Value of current (split) bet for this Player
	Chip m_split_bet;
	// Current (split) hand of this Player
	Hand m_split_hand;
};

#endif