#ifndef ART_H
#define ART_H

#include <iostream>
#include <string>
#include <vector>
using std::ostream;
using std::cout;
using std::string;
using std::vector;

class Art
{
public:

	/***** Static Members *****/

	// Error code if trying to access layer out of bounds
	static const int OUT_OF_BOUNDS = 1;
	// Error code if layers are not constant width
	static const int WIDTH_NOT_CONST = 2;
	// Error code if provided width/length too small
	static const int DIM_TOO_SMALL = 3;

	/***** Manager Functions *****/

	// Default constructor
	Art();
	// Constructor with arguments for dimensions of this Art
	Art(int width, int height);
	// Copy constructor
	Art(const Art& other_art);
	// Destructor
	~Art();

	/***** Overloaded Operators *****/

	// Copy assignment operator
	Art operator=(const Art& other_art);
	// Ostream insertion operator
	friend ostream& operator<<(ostream& os, const Art& this_art);

	/***** Member Functions *****/

	// Returns layer at index
	string get_layer(int index) const;
	// Sets layer at index to new_layer
	void set_layer(int index, string new_layer);
	// Adds new_layer before layer at index
	void add_layer(int index, string new_layer);
	// Removes the layer at index
	void rem_layer(int index);
	// Returns height (number of layers) of this Art
	int height() const;
	// Returns width (number of characters per layer) of this Art
	int width() const;
	// Function for adding padding around this Art to achieve a desired width and height
	Art pad(int trgt_width, int trgt_height);
	// Function for removing any padding around this Art
	Art unpad();
	// Function for adding a box around this Art
	Art box();
	// Function for removing a box around this Art (if applicable)
	Art unbox();

private:

	/***** Static Members *****/

	// Static function determines whether a string contains only spaces (used in unpad() above)
	static bool all_space(string test_string);

	/***** Data Members *****/

	// String vector holding layers of this Art
	vector<string> m_layers;
};

#endif