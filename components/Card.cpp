#include "Card.h"

/***** Static Members *****/

// Static function to compare two Cards by suit first and then by rank
int Card::compare_by_suit(Card card1, Card card2)
{
	int result;

	if (card1.m_suit > card2.m_suit)
	{
		result = 1;
	}
	else if (card1.m_suit < card2.m_suit)
	{
		result = -1;
	}
	else
	{
		if (card1.m_rank > card2.m_rank)
			result = 1;
		else if (card1.m_rank < card2.m_rank)
			result = -1;
		else
			result = 0;
	}

	return result;
}

// Static function to compare two Cards by rank first and then by suit
int Card::compare_by_rank(Card card1, Card card2)
{
	int result;

	if (card1.m_rank > card2.m_rank)
	{
		result = 1;
	}
	else if (card1.m_rank < card2.m_rank)
	{
		result = -1;
	}
	else
	{
		if (card1.m_suit > card2.m_suit)
			result = 1;
		else if (card1.m_suit < card2.m_suit)
			result = -1;
		else
			result = 0;
	}

	return result;
}

/***** Manager Functions *****/

// Default constructor
Card::Card() : m_rank(), m_suit(), m_side(true)
{}

// Constructor with int arguments for Rank and Suit
Card::Card(int rank, int suit, bool side) : m_rank(rank), m_suit(suit), m_side(side)
{}

// Constructor with string arguments for Rank and Suit
Card::Card(string rank, string suit, bool side) : m_rank(rank), m_suit(suit), m_side(side)
{}

// Copy constructor
Card::Card(const Card& other_card) : m_rank(other_card.m_rank), m_suit(other_card.m_suit), m_side(other_card.m_side)
{}

// Destructor
Card::~Card()
{}

/***** Overloaded Operations *****/

// Copy assignment operator
Card Card::operator=(const Card& other_card)
{
	if (this != &other_card)
	{
		m_rank = other_card.m_rank;
		m_suit = other_card.m_suit;
		m_side = other_card.m_side;
	}

	return *this;
}

// Equalily comparison operator
bool Card::operator==(const Card& other_card)
{
	return (m_rank == other_card.m_rank) && (m_suit == other_card.m_suit);
}

/***** Member Functions *****/

// Returns suit of this card
Suit Card::suit()
{
	return m_suit;
}

// Returns rank of this card
Rank Card::rank()
{
	return m_rank;
}

// Returns name of this Card
string Card::name()
{
	return m_rank.name() + " of " + m_suit.name();
}

// Returns abbreviation of this Card
string Card::abbrev()
{
	return m_rank.abbrev() + " " + m_rank.abbrev();
}

// Flips this Card face up
void Card::up()
{
	m_side = true;
}

// Flips this Card face down
void Card::down()
{
	m_side = false;
}

// Returns Art of this Card
Art Card::art(bool zoom)
{
	Art card_art;

	if (zoom) // Zoomed in
	{
		card_art = Art(11, 8);

		card_art.set_layer(0, ".---------.");
		card_art.set_layer(7, "'---------'");

		if (m_side) // Face up
		{
			Art suit_symbol = m_suit.large_symbol();

			card_art.set_layer(1, "| " + m_rank.abbrev() + (m_rank == 10 ? "      |" : "       |"));
			card_art.set_layer(6, (m_rank == 10 ? "|      " : "|       ") + m_rank.abbrev() + " |");

			for (int i = 0; i < suit_symbol.height(); ++i)
				card_art.set_layer(i + 2, "|  " + suit_symbol.get_layer(i) + "  |");
		}
		else // Face down
		{
			for (int i = 1; i < 4; ++i)
			{
				card_art.set_layer(2 * i - 1, "|/////////|");
				card_art.set_layer(2 * i, "|\\\\\\\\\\\\\\\\\\|");
			}
		}
	}
	else // Zoomed out
	{
		card_art = Art(5, 4);

		card_art.set_layer(0, ".---.");
		card_art.set_layer(3, "'---'");

		if (m_side) // Face up
		{
			card_art.set_layer(1, "|" + m_rank.abbrev() + (m_rank == 10 ? " |" : "  |"));
			card_art.set_layer(2, "| " + m_suit.small_symbol() + "|");
		}
		else // Face down
		{
			card_art.set_layer(1, "|///|");
			card_art.set_layer(2, "|\\\\\\|");
		}
	}

	return card_art;
}