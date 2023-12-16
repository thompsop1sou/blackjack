#include "Player.h"

/***** Manager Functions *****/

// Default constructor
Player::Player() : m_stack(), m_bet(), m_hand(), m_split_bet(), m_split_hand()
{}

// Destructor
Player::~Player()
{}

/***** Members Functions *****/

// Returns the Chip m_stack of this Player by reference
Chip& Player::stack()
{
	return m_stack;
}

// Returns the Chip m_bet of this Player by reference
Chip& Player::bet()
{
	return m_bet;
}

// Returns the Hand m_hand of this Player by reference
Hand& Player::hand()
{
	return m_hand;
}

// Returns the Chip m_split_bet of this Player by reference
Chip& Player::split_bet()
{
	return m_split_bet;
}

// Returns the Hand m_split_hand of this Player by reference
Hand& Player::split_hand()
{
	return m_split_hand;
}

// Returns title of this Player
Art Player::title(bool zoom)
{
	Art dealer_title;

	if (zoom)
		dealer_title.add_layer(0, "====================================== PLAYER =======================================");
	else
		dealer_title.add_layer(0, "===================== PLAYER ======================");

	return dealer_title;
}

// Returns Art of this Player
Art Player::art(bool zoom)
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