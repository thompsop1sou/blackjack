#pragma once

#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::cin;
using std::string;
using std::vector;

#include "Deck.h"
#include "Hand.h"
#include "Art.h"

class Dealer
{

public:

	/***** Manager Functions *****/

	// Default constructor
	Dealer() : m_shoe(6), m_discard(0), m_hand()
	{
		m_shoe.shuffle();
	}

	// Constructor with argument for number of decks in shoe
	Dealer(int num_decks) : m_shoe(num_decks), m_discard(0), m_hand()
	{
		m_shoe.shuffle();
	}

	// Destructor
	~Dealer()
	{}

	/***** Members Functions *****/

	// Returns the Deck m_shoe of this Dealer by reference
	Deck& shoe()
	{
		return m_shoe;
	}

	// Returns the Deck m_discard of this Dealer by reference
	Deck& discard()
	{
		return m_discard;
	}

	// Returns the Hand m_hand of this Dealer by reference
	Hand& hand()
	{
		return m_hand;
	}

	// Returns title of this Dealer
	Art title(bool zoom = true)
	{
		Art dealer_title;

		if (zoom)
			dealer_title.add_layer(0, "====================================== DEALER =======================================");
		else
			dealer_title.add_layer(0, "===================== DEALER ======================");

		return dealer_title;
	}

	// Returns Art of this Dealer
	Art art(bool zoom = true)
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

private:

	/***** Data Members *****/

	// "Shoe" (i.e. deck) to deal Cards from
	Deck m_shoe;

	// Discard pile to send used Cards to
	Deck m_discard;

	// Current hand of this Dealer
	Hand m_hand;

};