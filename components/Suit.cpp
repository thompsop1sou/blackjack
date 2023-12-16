#include "Suit.h"

/***** Manager Functions *****/

// Default constructor
Suit::Suit() : m_suit(0)
{}

// Constructor with int argument
Suit::Suit(int suit) : m_suit()
{
	if (suit > -1 && suit < 4)
		m_suit = suit;
	else
		m_suit = 0;
}

// Constructor with string argument
Suit::Suit(string suit) : m_suit()
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
Suit::Suit(const Suit& other_suit) : m_suit(other_suit.m_suit)
{}

// Destructor
Suit::~Suit()
{}

/***** Overloaded Operations *****/

// Copy assignment operator
Suit Suit::operator=(const Suit& other_suit)
{
	if (this != &other_suit)
		m_suit = other_suit.m_suit;

	return *this;
}

// Equal to comparison operator
bool Suit::operator==(const Suit& other_suit)
{
	return (m_suit == other_suit.m_suit);
}

// Greater than comparison operator
bool Suit::operator>(const Suit& other_suit)
{
	return (m_suit > other_suit.m_suit);
}

// Less than comparison operator
bool Suit::operator<(const Suit& other_suit)
{
	return (m_suit < other_suit.m_suit);
}

// Greater than or equal to comparison operator
bool Suit::operator>=(const Suit& other_suit)
{
	return  (m_suit >= other_suit.m_suit);
}

// Less than or equal to comparison operator
bool Suit::operator<=(const Suit& other_suit)
{
	return  (m_suit <= other_suit.m_suit);
}

/***** Member Functions *****/

// Returns name of this Suit
string Suit::name()
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
string Suit::abbrev()
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
string Suit::small_symbol()
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
Art Suit::large_symbol()
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