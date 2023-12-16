#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
using std::cout;
using std::string;
using std::vector;

#include "Card.h"
#include "Art.h"

class CardSet
{

public:

	/***** Manager Functions *****/

	// Default constructor
	CardSet() : m_cards()
	{}

	// Destructor
	~CardSet()
	{}

	/***** Members Functions *****/
	
	// Draws Cards from the other CardSet to this CardSet
	void draw(CardSet& other_set, int num_cards = 1, bool side = false)
	{
		if (num_cards < 0)
			num_cards = 0;
		else if (num_cards > other_set.m_cards.size())
			num_cards = other_set.m_cards.size();

		for (int i = 0; i < num_cards; ++i)
		{
			Card drawn_card = other_set.m_cards.back();
			other_set.m_cards.pop_back();

			if (side)
				drawn_card.up();
			else
				drawn_card.down();

			m_cards.push_back(drawn_card);
		}
	}

	// Deals Cards from this CardSet to the other CardSet
	void deal(CardSet& other_set, int num_cards = 1, bool side = false)
	{
		if (num_cards < 0)
			num_cards = 0;
		else if (num_cards > m_cards.size())
			num_cards = m_cards.size();

		for (int i = 0; i < num_cards; ++i)
		{
			Card dealt_card = m_cards.back();
			m_cards.pop_back();

			if (side)
				dealt_card.up();
			else
				dealt_card.down();

			other_set.m_cards.push_back(dealt_card);
		}
	}

	// Discards this CardSet into the other CardSet
	void discard(CardSet& other_set)
	{
		other_set.m_cards.insert(other_set.m_cards.end(), m_cards.begin(), m_cards.end());
		m_cards.clear();
	}

	// Collects the other CardSet into this CardSet
	void collect(CardSet& other_set)
	{
		m_cards.insert(m_cards.end(), other_set.m_cards.begin(), other_set.m_cards.end());
		other_set.m_cards.clear();
	}

	// Shuffles this CardSet
	void shuffle()
	{
		std::shuffle(m_cards.begin(), m_cards.end(), std::random_device());
	}

	// Sorts this CardSet first by suits and then by rank
	void sort_by_suit()
	{
		std::sort(m_cards.begin(), m_cards.end(), [](Card card1, Card card2) -> bool { return Card::compare_by_suit(card1, card2) == 1; });
	}

	// Sorts this CardSet first by rank and then by suit
	void sort_by_rank()
	{
		std::sort(m_cards.begin(), m_cards.end(), [](Card card1, Card card2) -> bool { return Card::compare_by_rank(card1, card2) == 1; });
	}

	// Returns number of Cards in this CardSet
	int count()
	{
		return m_cards.size();
	}

	// Sets all Cards in this CardSet so they are face up
	void all_up()
	{
		for (int i = 0; i < m_cards.size(); ++i)
			m_cards[i].up();
	}

	// Sets all Cards in this CardSet so they are face down
	void all_down()
	{
		for (int i = 0; i < m_cards.size(); ++i)
			m_cards[i].down();
	}

protected:

	/***** Data Members *****/

	// Vector holding all Cards in this CardSet
	vector<Card> m_cards;

};

