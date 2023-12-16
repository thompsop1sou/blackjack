#include "Deck.h"

/***** Manager Functions *****/

// Default constructor that creates one 52-card deck
Deck::Deck() : CardSet()
{
	for (int s = 0; s < 4; ++s)
	{
		for (int r = 1; r < 14; ++r)
			m_cards.push_back(Card(r, s, false));
	}
}

// Constructor with argument for number of 52-card decks
Deck::Deck(int num_decks) : CardSet()
{
	if (num_decks < 0)
		num_decks = 0;

	for (int d = 0; d < num_decks; ++d)
	{
		for (int s = 0; s < 4; ++s)
		{
			for (int r = 1; r < 14; ++r)
				m_cards.push_back(Card(r, s, false));
		}
	}
}

/***** Member Functions *****/

// Returns Art of this Deck
Art Deck::art(bool zoom)
{
	Art deck_art;

	if (m_cards.size() > 0)
	{
		Art card_art = m_cards.back().art(zoom);

		deck_art.add_layer(0, "." + card_art.get_layer(0));

		for (int i = 1; i < card_art.height() - 1; ++i)
			deck_art.add_layer(i, "|" + card_art.get_layer(i));

		deck_art.add_layer(deck_art.height(), "'" + card_art.get_layer(card_art.height() - 1));
	}
	else // m_cards.size() == 0
	{
		if (zoom) // Zoomed in
		{
			deck_art.add_layer(0, "' - - - - '");

			for (int i = 0; i < 6; ++i)
				deck_art.add_layer(0, "'         '");

			deck_art.add_layer(0, " - - - - - ");
		}
		else // Zoomed out 
		{
			deck_art.add_layer(0, "' - '");
			deck_art.add_layer(0, "'   '");
			deck_art.add_layer(0, "'   '");
			deck_art.add_layer(0, " - - ");
		}
	}

	return deck_art;
}