#include "Dealer.h"

/***** Manager Functions *****/

// Default constructor
Dealer::Dealer() : m_shoe(6), m_discard(0), m_hand()
{
	m_shoe.shuffle();
}

// Constructor with argument for number of decks in shoe
Dealer::Dealer(int num_decks) : m_shoe(num_decks), m_discard(0), m_hand()
{
	m_shoe.shuffle();
}

// Destructor
Dealer::~Dealer()
{}

/***** Members Functions *****/

// Returns the Deck m_shoe of this Dealer by reference
Deck& Dealer::shoe()
{
	return m_shoe;
}

// Returns the Deck m_discard of this Dealer by reference
Deck& Dealer::discard()
{
	return m_discard;
}

// Returns the Hand m_hand of this Dealer by reference
Hand& Dealer::hand()
{
	return m_hand;
}

// Returns title of this Dealer
Art Dealer::title(bool zoom)
{
	Art dealer_title;

	if (zoom)
		dealer_title.add_layer(0, "====================================== DEALER =======================================");
	else
		dealer_title.add_layer(0, "===================== DEALER ======================");

	return dealer_title;
}

// Returns Art of this Dealer
Art Dealer::art(bool zoom)
{
	Art dealer_art;

	int height = (zoom ? 8 : 4);
	int width1 = (zoom ? 16 : 8);
	int width2 = (zoom ? 49 : 31);

	Art shoe_art = m_shoe.art(zoom).pad(width1, height);
	Art discard_art = m_discard.art(zoom).pad(width1, height);
	Art hand_art = m_hand.art(zoom).pad(width2, height);

	if (zoom) // Zoomed in
		dealer_art.add_layer(0, "'----------------'----------------'-------------------------------------------------'");
	else // Zoomed out
		dealer_art.add_layer(0, "'--------'--------'-------------------------------'");

	for (int i = 0; i < height; ++i)
		dealer_art.add_layer(0, "|" + shoe_art.get_layer(height - i - 1) + "|" + discard_art.get_layer(height - i - 1) + "|" + hand_art.get_layer(height - i - 1) + "|");

	if (zoom) // Zoomed in
		dealer_art.add_layer(0, ".----- Shoe -----.--- Discard ----.--------------------- Hand ----------------------.");
	else // Zoomed out
		dealer_art.add_layer(0, ".- Shoe -.- Dscd -.------------ Hand -------------.");

	return dealer_art;
}