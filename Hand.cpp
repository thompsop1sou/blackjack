#include "Hand.h"

/***** Manager Functions *****/

// Default constructor
Hand::Hand() : CardSet(), m_spread(true)
{}

// Destructor
Hand::~Hand()
{}

/***** Member Functions *****/

// Returns blackjack score of this Hand
int Hand::score()
{
	int total_score = 0;
	int elevens = 0;

	for (int i = 0; i < m_cards.size(); ++i)
	{
		char rank_abbrev = m_cards[i].rank().abbrev()[0];

		switch (rank_abbrev)
		{
		case 'A':
			total_score += 11;
			++elevens;
			break;
		case '2':
			total_score += 2;
			break;
		case '3':
			total_score += 3;
			break;
		case '4':
			total_score += 4;
			break;
		case '5':
			total_score += 5;
			break;
		case '6':
			total_score += 6;
			break;
		case '7':
			total_score += 7;
			break;
		case '8':
			total_score += 8;
			break;
		case '9':
			total_score += 9;
			break;
		default:
			total_score += 10;
			break;
		}
	}

	while (total_score > 21 && elevens > 0)
	{
		--elevens;
		total_score -= 10;
	}

	return total_score;
}

// Returns true if this Hand can be split (per Blackjack rules)
bool Hand::splittable()
{
	bool results = false;

	if (m_cards.size() == 2)
	{
		if (m_cards[0].rank() > Card(9, 0).rank() && m_cards[1].rank() > Card(9, 0).rank())
			results = true;
		else
			results = (m_cards[0].rank() == m_cards[1].rank());
	}
	else
	{
		results = false;
	}

	return results;
}

// Returns Art of this Hand
Art Hand::art(bool zoom)
{
	Art hand_art;

	if (m_cards.size() > 0)
	{
		if ((zoom && m_cards.size() < 5) || (!zoom && m_cards.size() < 6)) // Expanded
		{
			Art card_art = m_cards.front().art(zoom);
			string new_layer;

			for (int i = 0; i < card_art.height(); ++i)
			{
				new_layer = card_art.get_layer(i);

				for (int j = 1; j < m_cards.size(); ++j)
					new_layer += " " + m_cards[j].art(zoom).get_layer(i);

				hand_art.add_layer(i, new_layer);
			}
		}
		else // Condensed
		{
			int width = (zoom ? 6 : 4);
			Art card_art = m_cards.back().art(zoom);
			string new_layer;

			for (int i = 0; i < card_art.height(); ++i)
			{
				new_layer = card_art.get_layer(i);

				for (int j = 1; j < m_cards.size(); ++j)
					new_layer = m_cards[m_cards.size() - j - 1].art(zoom).get_layer(i).substr(0, width) + new_layer;

				hand_art.add_layer(i, new_layer);
			}
		}
	}
	else // m_cards.size() == 0
	{
		if (zoom) // Zoomed in
		{
			hand_art.add_layer(0, "' - - - - '");

			for (int i = 0; i < 6; ++i)
				hand_art.add_layer(0, "'         '");

			hand_art.add_layer(0, " - - - - - ");
		}
		else // Zoomed out
		{
			hand_art.add_layer(0, "' - '");
			hand_art.add_layer(0, "'   '");
			hand_art.add_layer(0, "'   '");
			hand_art.add_layer(0, " - - ");
		}
	}

	return hand_art;
}