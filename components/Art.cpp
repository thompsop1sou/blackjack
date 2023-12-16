#include "Art.h"

/***** Manager Functions *****/

// Default constructor
Art::Art() : m_layers()
{}

// Constructor with arguments for dimensions of this Art
Art::Art(int width, int height) : m_layers()
{
	if (width > 0 && height > 0)
	{
		for (int i = 0; i < height; ++i)
		{
			m_layers.push_back(string(width, ' '));
		}
	}
}

// Copy constructor
Art::Art(const Art& other_art) : m_layers(other_art.m_layers)
{}

// Destructor
Art::~Art()
{}

/***** Overloaded Operators *****/

// Copy assignment operator
Art Art::operator=(const Art& other_art)
{
	if (this != &other_art)
		m_layers = other_art.m_layers;

	return *this;
}

// Ostream insertion operator
ostream& operator << (ostream& os, const Art& this_art)
{
	if (this_art.m_layers.size() > 0)
	{
		for (int i = 0; i < this_art.m_layers.size() - 1; ++i)
			cout << this_art.m_layers[i] << '\n';
		cout << this_art.m_layers[this_art.height() - 1];
	}

	return os;
}

/***** Member Functions *****/

// Returns layer at index
string Art::get_layer(int index) const
{
	if (index < 0 || index >= m_layers.size())
		throw OUT_OF_BOUNDS;

	return m_layers[index];
}

// Sets layer at index to new_layer
void Art::set_layer(int index, string new_layer)
{
	if (index < 0 || index >= m_layers.size())
		throw OUT_OF_BOUNDS;

	if (new_layer.length() != width())
		throw WIDTH_NOT_CONST;

	m_layers[index] = new_layer;
}

// Adds new_layer before layer at index
void Art::add_layer(int index, string new_layer)
{
	if (index < 0 || index > m_layers.size())
		throw OUT_OF_BOUNDS;

	if (m_layers.size() > 0 && new_layer.length() != width())
		throw WIDTH_NOT_CONST;

	m_layers.insert(m_layers.begin() + index, new_layer);
}

// Removes the layer at index
void Art::rem_layer(int index)
{
	if (index < 0 || index >= m_layers.size())
		throw OUT_OF_BOUNDS;

	m_layers.erase(m_layers.begin() + index);
}

// Returns height (number of layers) of this Art
int Art::height() const
{
	return m_layers.size();
}

// Returns width (number of characters per layer) of this Art
int Art::width() const
{
	int width;

	if (m_layers.size() > 0)
	{
		width = m_layers[0].length();
		for (int i = 1; i < m_layers.size(); ++i)
		{
			if (width != m_layers[i].length())
				throw WIDTH_NOT_CONST;
		}
	}
	else
	{
		width = 0;
	}

	return width;
}

// Function for adding padding around this Art to achieve a desired width and height
Art Art::pad(int trgt_width, int trgt_height)
{
	int curr_width = width();
	int curr_height = height();

	// Making sure target dimensions are not too small
	if (trgt_width < curr_width || trgt_height < curr_height)
		throw DIM_TOO_SMALL;

	// Padding around sides
	if ((trgt_width - curr_width) % 2 == 0)
	{
		for (int i = 0; i < curr_height; ++i)
			m_layers[i] = string((trgt_width - curr_width) / 2, ' ') + m_layers[i] + string((trgt_width - curr_width) / 2, ' ');
	}
	else
	{
		for (int i = 0; i < curr_height; ++i)
			m_layers[i] = string((trgt_width - curr_width) / 2, ' ') + m_layers[i] + string(1 + (trgt_width - curr_width) / 2, ' ');
	}
	
	// Padding around top and bottom
	if ((trgt_height - curr_height) % 2 == 0)
	{
		for (int i = 0; i < (trgt_height - curr_height) / 2; ++i)
		{
			m_layers.insert(m_layers.begin(), string(trgt_width, ' '));
			m_layers.insert(m_layers.end(), string(trgt_width, ' '));
		}
	}
	else
	{
		for (int i = 0; i < (trgt_height - curr_height) / 2; ++i)
		{
			m_layers.insert(m_layers.begin(), string(trgt_width, ' '));
			m_layers.insert(m_layers.end(), string(trgt_width, ' '));
		}
		m_layers.insert(m_layers.end(), string(trgt_width, ' '));
	}

	return *this;
}

// Function for removing any padding around this Art
Art Art::unpad()
{
	int top_pad = 0,
		bot_pad = 0,
		lft_pad = 1000,
		rht_pad = 1000,
		curr_lft_pad,
		curr_rht_pad;

	// Removing padding from top
	while (top_pad < m_layers.size() && all_space(m_layers[top_pad]))
		++top_pad;

	for (int i = 0; i < top_pad; ++i)
		m_layers.erase(m_layers.begin());
		
	// Removing padding from bottom
	while (bot_pad < m_layers.size() && all_space(m_layers[m_layers.size() - bot_pad - 1]))
		++bot_pad;

	for (int i = 0; i < bot_pad; ++i)
		m_layers.erase(m_layers.end() - 1);

	// Removing padding from sides
	for (int i = 0; i < m_layers.size(); ++i)
	{
		curr_lft_pad = 0;
		curr_rht_pad = 0;

		while (m_layers[i][curr_lft_pad] == ' ')
			++curr_lft_pad;

		lft_pad = (lft_pad > curr_lft_pad ? curr_lft_pad : lft_pad);

		while (m_layers[i][m_layers[i].length() - curr_rht_pad - 1] == ' ')
			++curr_rht_pad;

		rht_pad = (rht_pad > curr_rht_pad ? curr_rht_pad : rht_pad);
	}

	for (int i = 0; i < m_layers.size(); ++i)
		m_layers[i] = m_layers[i].substr(lft_pad, (m_layers[i].length() - rht_pad - lft_pad));

	return *this;
}

// Function for adding a box around this Art
Art Art::box()
{
	int curr_width = width();
	int curr_height = height();

	// Adding box to sides
	for (int i = 0; i < curr_height; ++i)
		m_layers[i] = "|" + m_layers[i] + "|";

	// Adding box to top and bottom
	m_layers.insert(m_layers.begin(), ("." + string(curr_width, '-') + "."));
	m_layers.insert(m_layers.end(), ("'" + string(curr_width, '-') + "'"));

	return *this;
}

// Function for removing a box around this Art (if applicable)
Art Art::unbox()
{
	if (height() > 0 && width() > 0)
	{
		string top = m_layers[0];
		string bot = m_layers[m_layers.size() - 1];
		string curr_layer;

		// Making sure there is a box on top
		bool top_boxed = (top[0] == '.') && (top[top.length() - 1] == '.');
		if (top_boxed)
		{
			for (int i = 1; i < top.length() - 1; ++i)
			{
				if (top[i] != '-')
				{
					top_boxed = false;
					break;
				}
			}
		}

		// Making sure there is a box on the bottom
		bool bot_boxed = (bot[0] == '\'') && (bot[bot.length() - 1] == '\'');
		if (bot_boxed)
		{
			for (int i = 1; i < bot.length() - 1; ++i)
			{
				if (bot[i] != '-')
				{
					bot_boxed = false;
					break;
				}
			}
		}

		// Making sure there is a box around the sides
		bool sides_boxed = true;
		for (int i = 1; i < m_layers.size() - 1; ++i)
		{
			curr_layer = m_layers[i];
			if (curr_layer[0] != '|' || curr_layer[curr_layer.length() - 1] != '|')
			{
				sides_boxed = false;
				break;
			}
		}

		// Getting rid of box (if it is there)
		if (top_boxed && bot_boxed && sides_boxed)
		{
			m_layers.erase(m_layers.begin());
			m_layers.erase(m_layers.end() - 1);

			for (int i = 0; i < m_layers.size(); ++i)
				m_layers[i] = m_layers[i].substr(1, (m_layers[i].length() - 2));
		}
	}

	return *this;
}

/***** Static Members *****/

// Static function determines whether a string contains only spaces (used in unpad() above)
bool Art::all_space(string test_string)
{
	bool result = true;

	for (int i = 0; i < test_string.length(); ++i)
	{
		if (test_string[i] != ' ')
		{
			result = false;
			break;
		}
	}

	return result;
}