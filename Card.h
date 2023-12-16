#pragma once

#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::string;
using std::vector;

#include "Art.h"

class Rank
{

public:

	/***** Manager Functions *****/

	// Default constructor
	Rank() : m_rank(1)
	{}

	// Constructor with int argument
	Rank(int rank) : m_rank()
	{
		if (rank > 0 && rank < 14)
			m_rank = rank;
		else
			m_rank = 1;
	}

	// Constructor with string argument
	Rank(string rank) : m_rank()
	{
		for (int i = 0; i < rank.length(); ++i)
			rank[i] = tolower(rank[i]);

		if (rank == "2" || rank == "two")
			m_rank = 2;
		else if (rank == "3" || rank == "three")
			m_rank = 3;
		else if (rank == "4" || rank == "four")
			m_rank = 4;
		else if (rank == "5" || rank == "five")
			m_rank = 5;
		else if (rank == "6" || rank == "six")
			m_rank = 6;
		else if (rank == "7" || rank == "seven")
			m_rank = 7;
		else if (rank == "8" || rank == "eight")
			m_rank = 8;
		else if (rank == "9" || rank == "nine")
			m_rank = 9;
		else if (rank == "10" || rank == "ten")
			m_rank = 10;
		else if (rank == "j" || rank == "jack")
			m_rank = 11;
		else if (rank == "q" || rank == "queen")
			m_rank = 12;
		else if (rank == "k" || rank == "king")
			m_rank = 13;
		else
			m_rank = 1;
	}

	// Copy constructor
	Rank(const Rank& other_rank) : m_rank(other_rank.m_rank)
	{}

	// Destructor
	~Rank()
	{}

	/***** Overloaded Operations *****/

	// Copy assignment operator
	Rank operator=(const Rank& other_rank)
	{
		if (this != &other_rank)
			m_rank = other_rank.m_rank;

		return *this;
	}

	// Equal to comparison operator
	bool operator==(const Rank& other_rank)
	{
		return (m_rank == other_rank.m_rank);
	}

	// Greater than comparison operator
	bool operator>(const Rank& other_rank)
	{
		return (m_rank > other_rank.m_rank);
	}

	// Less than comparison operator
	bool operator<(const Rank& other_rank)
	{
		return (m_rank < other_rank.m_rank);
	}

	// Greater than or equal to comparison operator
	bool operator>=(const Rank& other_rank)
	{
		return  (m_rank >= other_rank.m_rank);
	}

	// Less than or equal to comparison operator
	bool operator<=(const Rank& other_rank)
	{
		return  (m_rank <= other_rank.m_rank);
	}

	/***** Member Functions *****/

	// Returns abbreviation of this Rank
	string name()
	{
		string name;

		switch (m_rank)
		{
		case 1: name = "Ace"; break;
		case 2: name = "Two"; break;
		case 3: name = "Three"; break;
		case 4: name = "Four"; break;
		case 5: name = "Five"; break;
		case 6: name = "Six"; break;
		case 7: name = "Seven"; break;
		case 8: name = "Eight"; break;
		case 9: name = "Nine"; break;
		case 10: name = "Ten"; break;
		case 11: name = "Jack"; break;
		case 12: name = "Queen"; break;
		case 13: name = "King"; break;
		}

		return name;
	}

	// Returns abbreviation of this Rank
	string abbrev()
	{
		string abbrev;

		switch (m_rank)
		{
		case 1: abbrev = "A"; break;
		case 2: abbrev = "2"; break;
		case 3: abbrev = "3"; break;
		case 4: abbrev = "4"; break;
		case 5: abbrev = "5"; break;
		case 6: abbrev = "6"; break;
		case 7: abbrev = "7"; break;
		case 8: abbrev = "8"; break;
		case 9: abbrev = "9"; break;
		case 10: abbrev = "10"; break;
		case 11: abbrev = "J"; break;
		case 12: abbrev = "Q"; break;
		case 13: abbrev = "K"; break;
		}

		return abbrev;
	}

private:

	/***** Data Member *****/

	// Int holding rank value (from 1 to 13)
	int m_rank;

};

class Suit
{

public:

	/***** Manager Functions *****/

	// Default constructor
	Suit() : m_suit(0)
	{}

	// Constructor with int argument
	Suit(int suit) : m_suit()
	{
		if (suit > -1 && suit < 4)
			m_suit = suit;
		else
			m_suit = 0;
	}

	// Constructor with string argument
	Suit(string suit) : m_suit()
	{
		for (int i = 0; i < suit.length(); ++i)
			suit[i] = tolower(suit[i]);

		if (suit == "c" || suit == "clubs")
			m_suit = 1;
		else if (suit == "d" || suit == "diamonds")
			m_suit = 2;
		else if (suit == "s" || suit == "spades")
			m_suit = 3;
		else
			m_suit = 0;
	}

	// Copy constructor
	Suit(const Suit& other_suit) : m_suit(other_suit.m_suit)
	{}

	// Destructor
	~Suit()
	{}

	/***** Overloaded Operations *****/

	// Copy assignment operator
	Suit operator=(const Suit& other_suit)
	{
		if (this != &other_suit)
			m_suit = other_suit.m_suit;

		return *this;
	}

	// Equal to comparison operator
	bool operator==(const Suit& other_suit)
	{
		return (m_suit == other_suit.m_suit);
	}

	// Greater than comparison operator
	bool operator>(const Suit& other_suit)
	{
		return (m_suit > other_suit.m_suit);
	}

	// Less than comparison operator
	bool operator<(const Suit& other_suit)
	{
		return (m_suit < other_suit.m_suit);
	}

	// Greater than or equal to comparison operator
	bool operator>=(const Suit& other_suit)
	{
		return  (m_suit >= other_suit.m_suit);
	}

	// Less than or equal to comparison operator
	bool operator<=(const Suit& other_suit)
	{
		return  (m_suit <= other_suit.m_suit);
	}

	/***** Member Functions *****/

	// Returns abbreviation of this Suit
	string name()
	{
		string name;

		switch (m_suit)
		{
		case 0: name = "Hearts"; break;
		case 1: name = "Clubs"; break;
		case 2: name = "Diamonds"; break;
		case 3: name = "Spades"; break;
		}

		return name;
	}

	// Returns abbreviation of this Suit
	string abbrev()
	{
		string abbrev;

		switch (m_suit)
		{
		case 0: abbrev = "H"; break;
		case 1: abbrev = "C"; break;
		case 2: abbrev = "D"; break;
		case 3: abbrev = "S"; break;
		}

		return abbrev;
	}
	// Returns small symbol of this Suit
	string small_symbol()
	{
		string symbol;

		switch (m_suit)
		{
		case 0: symbol = "<3"; break;
		case 1: symbol = "{o"; break;
		case 2: symbol = "<>"; break;
		case 3: symbol = "{>"; break;
		}

		return symbol;
	}

	// Returns large symbol of this Suit
	Art large_symbol()
	{
		Art symbol(5, 4);

		switch (m_suit)
		{
		case 0:
			symbol.set_layer(0, " _ _ ");
			symbol.set_layer(1, "( V )");
			symbol.set_layer(2, " \\ / ");
			symbol.set_layer(3, "  '  ");
			break;
		case 1:
			symbol.set_layer(0, "  _  ");
			symbol.set_layer(1, " ( ) ");
			symbol.set_layer(2, "(_ _)");
			symbol.set_layer(3, "  ^  ");
			break;
		case 2:
			symbol.set_layer(0, "  .  ");
			symbol.set_layer(1, " / \\ ");
			symbol.set_layer(2, " \\ / ");
			symbol.set_layer(3, "  '  ");
			break;
		case 3:
			symbol.set_layer(0, "  .  ");
			symbol.set_layer(1, " / \\ ");
			symbol.set_layer(2, "(_ _)");
			symbol.set_layer(3, "  ^  ");
			break;
		}

		return symbol;
	}

private:

	/***** Data Member *****/

	// Int holding suit value (from 0 to 3)
	int m_suit;

};

class Card
{
public:

	/***** Static Members *****/

	// Static function to compare two Cards by suit first and then by rank
	static int compare_by_suit(Card card1, Card card2)
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
	static int compare_by_rank(Card card1, Card card2)
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
	Card() : m_rank(), m_suit(), m_side(true)
	{}

	// Constructor with int arguments for Rank and Suit
	Card(int rank, int suit, bool side = true) : m_rank(rank), m_suit(suit), m_side(side)
	{}

	// Constructor with string arguments for Rank and Suit
	Card(string rank, string suit, bool side = true) : m_rank(rank), m_suit(suit), m_side(side)
	{}

	// Copy constructor
	Card(const Card& other_card) : m_rank(other_card.m_rank), m_suit(other_card.m_suit), m_side(other_card.m_side)
	{}

	// Destructor
	~Card()
	{}

	/***** Overloaded Operations *****/

	// Copy assignment operator
	Card operator=(const Card& other_card)
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
	bool operator==(const Card& other_card)
	{
		return (m_rank == other_card.m_rank) && (m_suit == other_card.m_suit);
	}

	/***** Member Functions *****/

	Suit suit()
	{
		return m_suit;
	}

	Rank rank()
	{
		return m_rank;
	}

	// Returns name of this Card
	string name()
	{
		return m_rank.name() + " of " + m_suit.name();
	}

	// Returns abbreviation of this Card
	string abbrev()
	{
		return m_rank.abbrev() + " " + m_rank.abbrev();
	}

	// Flips this Card face up
	void up()
	{
		m_side = true;
	}

	// Flips this Card face down
	void down()
	{
		m_side = false;
	}

	// Returns Art of this Card
	Art art(bool zoom = true)
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

private:

	/***** Data Members *****/

	// Rank of this Card
	Rank m_rank;

	// Suit of this Card
	Suit m_suit;

	// Bool determining whether this card appears face-up (true) or face-down (false)
	bool m_side;

};