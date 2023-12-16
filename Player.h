#pragma once

#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::cin;
using std::string;
using std::vector;

#include "Hand.h"
#include "Chip.h"
#include "Art.h"

class Player
{

public:

	/***** Manager Functions *****/

	// Default constructor
	Player() : m_stack(), m_bet(), m_hand(), m_split_bet(), m_split_hand()
	{}

	// Destructor
	~Player()
	{}

	/***** Members Functions *****/

	// Returns the Chip m_stack of this Player by reference
	Chip& stack()
	{
		return m_stack;
	}

	// Returns the Chip m_bet of this Player by reference
	Chip& bet()
	{
		return m_bet;
	}

	// Returns the Hand m_hand of this Player by reference
	Hand& hand()
	{
		return m_hand;
	}

	// Returns the Chip m_split_bet of this Player by reference
	Chip& split_bet()
	{
		return m_split_bet;
	}

	// Returns the Hand m_split_hand of this Player by reference
	Hand& split_hand()
	{
		return m_split_hand;
	}

	// Returns title of this Player
	Art title(bool zoom = true)
	{
		Art dealer_title;

		if (zoom)
			dealer_title.add_layer(0, "====================================== PLAYER =======================================");
		else
			dealer_title.add_layer(0, "===================== PLAYER ======================");

		return dealer_title;
	}

	// Returns Art of this Player
	Art art(bool zoom = true)
	{
		Art player_art;

		int height = (zoom ? 8 : 4);
		int width1 = (zoom ? 16 : 8);
		int width2 = (zoom ? 49 : 31);

		if (m_split_hand.count() > 0)
		{
			Art blank_art = Art().pad(width1, height);
			Art split_bet_art = m_split_bet.art(zoom).pad(width1, height);
			Art split_hand_art = m_split_hand.art(zoom).pad(width2, height);

			if (zoom) // Zoomed in
				player_art.add_layer(0, "                 '----------------'-------------------------------------------------'");
			else // Zoomed out
				player_art.add_layer(0, "         '--------'-------------------------------'");

			for (int i = 0; i < height; ++i)
				player_art.add_layer(0, " " + blank_art.get_layer(height - i - 1) + "|" + split_bet_art.get_layer(height - i - 1) + "|" + split_hand_art.get_layer(height - i - 1) + "|");

			if (zoom) // Zoomed in
				player_art.add_layer(0, "                 .----- Bet ------.--------------------- Hand ----------------------.");
			else // Zoomed out
				player_art.add_layer(0, "         .- Bet --.------------ Hand -------------.");

			player_art.add_layer(0, string((zoom ? 85 : 51), ' '));
		}

		Art stack_art = m_stack.art(zoom).pad(width1, height);
		Art bet_art = m_bet.art(zoom).pad(width1, height);
		Art hand_art = m_hand.art(zoom).pad(width2, height);

		if (zoom) // Zoomed in
			player_art.add_layer(0, "'----------------'----------------'-------------------------------------------------'");
		else // Zoomed out
			player_art.add_layer(0, "'--------'--------'-------------------------------'");

		for (int i = 0; i < height; ++i)
			player_art.add_layer(0, "|" + stack_art.get_layer(height - i - 1) + "|" + bet_art.get_layer(height - i - 1) + "|" + hand_art.get_layer(height - i - 1) + "|");

		if (zoom) // Zoomed in
			player_art.add_layer(0, ".---- Stack -----.----- Bet ------.--------------------- Hand ----------------------.");
		else // Zoomed out
			player_art.add_layer(0, ".- Stck -.- Bet --.------------ Hand -------------.");

		return player_art;
	}

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