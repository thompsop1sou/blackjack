#include "Input.h"

/***** Manager Functions *****/

// Default constructor
Input::Input() : m_kind(), m_choices(), m_prompt(), m_condition(), m_value()
{
	m_condition = [](string str) -> bool { return true; };
}

// Destructor
Input::~Input()
{}

/***** Public Member Functions *****/

// Returns value of this Input
int Input::value()
{
	return m_value;
}

// Sets kind of this Input
void Input::set_kind(Kind kind)
{
	m_kind = kind;
}

// Sets Choices of this Input
void Input::set_choices(vector<string> choices)
{
	m_choices = choices;
}

// Sets prompt of this Input
void Input::set_prompt(string prompt)
{
	m_prompt = prompt;
}

// Sets condition of this Input
void Input::set_condition(function<bool(string)> condition)
{
	m_condition = condition;
}

// Sets delay of this Input
void Input::set_delay(int delay)
{
	if (delay >= 0)
		m_delay = seconds(delay);
	else
		m_delay = seconds(0);
}

// Gets input value from user
void Input::retrieve()
{
	if (m_kind == None) // No input, delay
	{
		cout << "\n" << m_prompt;

		std::this_thread::sleep_for(m_delay);

		cout << endl;
	}
	else // Choice or Number input
	{
		bool cont = true;
		string input;

		while (cont)
		{
			cout << "\n" << m_prompt;
			getline(cin, input);

			if (m_condition(input)) // Passes m_condition
			{
				if (m_kind == Choice)
				{
					try
					{
						int temp_val = stoi(input);

						if (temp_val > 0 && temp_val <= m_choices.size())
						{
							m_value = temp_val - 1;
							cont = false;
						}
						else
						{
							cout << "\nINVALID INPUT" << endl;
							cont = true;
						}
					}
					catch (...)
					{
						int index = find(input, m_choices);

						if (index == -1)
						{
							cout << "\nINVALID INPUT" << endl;
							cont = true;
						}
						else
						{
							m_value = index;
							cont = false;
						}
					}
				}
				else if (m_kind == Number)
				{
					try
					{
						int temp_val = stoi(input);

						m_value = temp_val;
						cont = false;
					}
					catch (...)
					{
						cout << "\nINVALID INPUT" << endl;
						cont = true;
					}
				}
			}
			else // Failse m_condition
			{
				cout << "\nINVALID INPUT" << endl;
				cont = true;
			}
		}
	}
}

// Returns title of this Input
Art Input::title(bool zoom)
{
	Art action_title;

	if (zoom)
		action_title.add_layer(0, "======================================= INPUT =======================================");
	else
		action_title.add_layer(0, "====================== INPUT ======================");

	return action_title;
}

// Returns Art of this Input
Art Input::art(bool zoom)
{
	Art input_art;
	int tot_width = (zoom ? 85 : 51);

	if (m_choices.size() > 0)
	{
		int each_width = (tot_width - 1) / m_choices.size() - 1;
		int rem_width = tot_width - (each_width + 1) * m_choices.size() - 1;

		string top = ".";
		string mid = "|";
		string bot = "'";

		for (int i = 0; i < m_choices.size(); ++i)
		{
			int curr_width = each_width;
			if (rem_width > 0)
			{
				++curr_width;
				--rem_width;
			}

			top += string(curr_width, '-') + ".";
			bot += string(curr_width, '-') + "'";

			if ((curr_width - m_choices[i].length()) % 2 == 0)
				mid += string((curr_width - m_choices[i].length()) / 2, ' ') + m_choices[i] + string((curr_width - m_choices[i].length()) / 2, ' ') + "|";
			else
				mid += string((curr_width - m_choices[i].length()) / 2, ' ') + m_choices[i] + string(1 + (curr_width - m_choices[i].length()) / 2, ' ') + "|";
		}

		input_art.add_layer(0, top);
		input_art.add_layer(1, mid);
		input_art.add_layer(2, bot);
	}
	else // m_choices.size() == 0
	{
		input_art = Art(tot_width - 2, 1);
		input_art.box();
	}

	return input_art;
}

/***** Private Member Functions *****/

// Find index of elem in vect, returns -1 if not found
int Input::find(string elem, vector<string> vect, bool case_sens)
{
	int index = -1;

	if (case_sens)
	{
		for (int i = 0; i < vect.size(); ++i)
		{
			if (elem == vect[i])
			{
				index = i;
				break;
			}
		}
	}
	else
	{
		elem = to_lower(elem);

		for (int i = 0; i < vect.size(); ++i)
		{
			if (elem == to_lower(vect[i]))
			{
				index = i;
				break;
			}
		}
	}

	return index;
}

// Converts a string to lowercase
string Input::to_lower(string str)
{
	for (int i = 0; i < str.length(); ++i)
		str[i] = tolower(str[i]);

	return str;
}
