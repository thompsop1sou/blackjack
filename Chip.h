#pragma once

#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::cin;
using std::to_string;
using std::string;
using std::vector;

#include "Art.h"

class Chip
{

public:

	/***** Manager Functions *****/

	// Default constructor
	Chip() : m_value(0)
	{}

	// Constructor which takes argument for value of this Chip
	Chip(int value) : m_value(0)
	{
		if (value < 0)
			m_value = 0;
		else
			m_value = value;
	}

	// Copy constructor
	Chip(const Chip& other_chip) : m_value(other_chip.m_value)
	{}

	// Destructor
	~Chip()
	{}

	/***** Overloaded Operators *****/

	// Copy assignment operator
	Chip operator=(const Chip& other_chip)
	{
		if (this != &other_chip)
			m_value = other_chip.m_value;

		return *this;
	}

	/***** Member Functions *****/

	// Adds value to this Chip
	void add(int value)
	{
		m_value += value;
	}

	// Subtracts value from this Chip
	void sub(int value)
	{
		m_value -= value;
	}

	// Returns value of this Chip
	int value()
	{
		return m_value;
	}

	// Returns Art of this Chip
	Art art(bool zoom = true)
	{
		Art chip_art;
		string num;

		if (m_value >= 1000000000000)
			num = to_string(m_value / 1000000000000) + "T";
		else if (m_value >= 1000000000)
			num = to_string(m_value / 1000000000) + "B";
		else if (m_value >= 1000000)
			num = to_string(m_value / 1000000) + "M";
		else if (m_value >= 1000)
			num = to_string(m_value / 1000) + "K";
		else
			num = to_string(m_value);

		if ((4 - num.length()) % 2 == 0)
			num = string((4 - num.length()) / 2, ' ') + num + string((4 - num.length()) / 2, ' ');
		else
			num = string((4 - num.length()) / 2, ' ') + num + string(1 + (4 - num.length()) / 2, ' ');

		if (zoom) // Zoomed in
		{
			chip_art = Art(10, 6);
			chip_art.set_layer(0, "  .----.  ");
			chip_art.set_layer(1, " /      \\ ");
			chip_art.set_layer(2, "|  " + num + "  |");
			chip_art.set_layer(3, "|\\      /|");
			chip_art.set_layer(4, " \\'----'/ ");
			chip_art.set_layer(5, "  '----'  ");
		}
		else // Zoomed out
		{
			chip_art = Art(6, 4);
			chip_art.set_layer(0, " .--. ");
			chip_art.set_layer(1, "|" + num + "|");
			chip_art.set_layer(2, "|.__.|");
			chip_art.set_layer(3, " '--' ");
		}

		return chip_art;
	}

private:

	/***** Data Members *****/

	// Int holding value of this Chip
	int m_value;

};